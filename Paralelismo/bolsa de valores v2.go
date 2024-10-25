package main

import (
	"encoding/json"
	"fmt"
	"log"
	"math/rand"
	"sync"
	"sync/atomic"
	"time"
)

type Order struct {
	OrderID  string  `json:"order_id"`
	StockID  string  `json:"stock_id"`
	Type     string  `json:"type"` // "buy" ou "sell"
	Quantity int     `json:"quantity"`
	Executed int     `json:"executed"`
	Price    float64 `json:"price"`
	Status   string  `json:"status"` // "pending", "executed", "partially" ou "canceled"
}

type Stock struct {
	pending chan Order
	buy     chan Order
	sell    chan Order
}

var (
	queueStock                 = sync.Map{} // Cooperação entre goroutines, garantindo que todas terminem seu processamento antes de prosseguir. coordenando a sincronização sem causar condições de corrida.
	queueInput                 = make(chan Order, 1000)
	queueOutput                = make(chan Order, 1000)
	orderID     int64          = 0
	wgProcess   sync.WaitGroup // WaitGroup para sincronizar as goroutines de processamento
)

func main() {
	fmt.Printf("MERCADO ABRINDO, RECUPERANDO AS ORDENS ANTERIORES 'PENDENTE'S.\n\n\n")

	go processOrdersQueue()

	generateInitialOrders(500)

	startTime := time.Now()

	fmt.Printf("\n\n\nMERCADO ABERTO, PERMITIDO A EMISSÃO DE NOVAS ORDENS.\n\n\n")

	startStockWorkers()

	continueOrderGenerationAndProcessing(500)

	closeOrderQueue()

	fmt.Printf("\n\n\nMERCADO FECHADO, BLOQUEADO A EMISSÃO DE NOVAS ORDENS.\n\n\n")

	wgProcess.Wait()

	fmt.Printf("\n\n\nPROCESSAMENTO FINALIZADO, TODAS AS ORDENS FORAM PROCESSADAS.\n\n\n")

	cancelPendingOrders()

	fmt.Printf("\n\n\nEXECUÇÃO FINALIZADA, TODAS AS ORDENS PENDENTES FORAM CANCELADAS.\n")

	elapsedTime := time.Since(startTime)

	fmt.Printf("\n\nTempo de execução: %s\n", elapsedTime)
	fmt.Printf("Tamanho da fila de saída: %d\n", len(queueOutput))
}

func generateInitialOrders(n int) {
	for i := 0; i < n; i++ {
		order := createOrder()
		orderJson, err := json.Marshal(order)
		if err != nil {
			continue
		}
		addOrderToGlobalQueue(order)
		log.Printf("[?] Ordem recuperada para %s: %s\n", order.StockID, string(orderJson))
	}
}

func startStockWorkers() {
	queueStock.Range(func(key, value interface{}) bool {
		wgProcess.Add(1)
		go startStockWorker(key.(string))
		return true
	})
}

func continueOrderGenerationAndProcessing(n int) {
	for i := 0; i < n; i++ {
		order := createOrder()
		orderJson, err := json.Marshal(order)
		if err != nil {
			continue
		}
		addOrderToGlobalQueue(order)
		log.Printf("[?] Ordem emitida para %s: %s\n", order.StockID, string(orderJson))
		time.Sleep(time.Duration(rand.Intn(11)+15) * time.Millisecond)
	}
}

func addOrderToGlobalQueue(order Order) {
	queueInput <- order
}

func processOrdersQueue() {
	for order := range queueInput {
		enqueueWorker(order)
	}
}

func closeOrderQueue() {
	close(queueInput)
	queueStock.Range(func(_, value interface{}) bool {
		close(value.(*Stock).pending)
		return true
	})
}

func generateUniqueOrderID() string {
	id := atomic.AddInt64(&orderID, 1)
	return fmt.Sprintf("order-%d", id)
}

func createOrder() Order {
	return Order{
		OrderID:  generateUniqueOrderID(),
		StockID:  fmt.Sprintf("stock-%d", rand.Intn(10)),
		Type:     []string{"buy", "sell"}[rand.Intn(2)],
		Quantity: rand.Intn(100) + 1,
		Executed: 0,
		Price:    float64(rand.Intn(1000)) + rand.Float64(),
		Status:   "pending",
	}
}

func enqueueWorker(order Order) {
	orders, exists := queueStock.Load(order.StockID)
	if !exists {
		orders = &Stock{
			buy:     make(chan Order, 1000),
			sell:    make(chan Order, 1000),
			pending: make(chan Order, 1000),
		}
		queueStock.Store(order.StockID, orders)
	}
	orders.(*Stock).pending <- order
}

func startStockWorker(stockID string) {
	defer wgProcess.Done()

	orders, _ := queueStock.Load(stockID)
	for order := range orders.(*Stock).pending {
		log.Printf("[!] Worker da %s, processando a %v\n", stockID, order.OrderID)
		processOrder(order, orders.(*Stock))
	}
	close(orders.(*Stock).buy)
	close(orders.(*Stock).sell)
}

func processOrder(order Order, orders *Stock) {
	if order.Type == "buy" {
		processBuyOrder(order, orders)
	} else if order.Type == "sell" {
		processSellOrder(order, orders)
	}
}

func processBuyOrder(order Order, orders *Stock) {
	select {
	case sellOrder := <-orders.sell:
		processMatch(order, sellOrder, orders.buy, orders.sell)
	default:
		select {
		case orders.buy <- order:
		case sellOrder := <-orders.sell:
			processMatch(order, sellOrder, orders.buy, orders.sell)
		}
	}
}

func processSellOrder(order Order, orders *Stock) {
	select {
	case buyOrder := <-orders.buy:
		processMatch(buyOrder, order, orders.buy, orders.sell)
	default:
		select {
		case orders.sell <- order:
		case buyOrder := <-orders.buy:
			processMatch(buyOrder, order, orders.buy, orders.sell)
		}
	}
}

func processMatch(buyOrder, sellOrder Order, buyQueue, sellQueue chan Order) {
	if isMatchingOrder(buyOrder, sellOrder) {
		time.Sleep(time.Duration(rand.Intn(201)+300) * time.Millisecond)

		processedQuantity := determineProcessedQuantity(buyOrder, sellOrder)
		transactionValue := calculateTransactionValue(processedQuantity, sellOrder.Price)

		buyOrder.Executed += processedQuantity
		sellOrder.Executed += processedQuantity

		updateOrderStatus(&buyOrder, processedQuantity)
		updateOrderStatus(&sellOrder, processedQuantity)

		remainingBuyerQuantity := buyOrder.Quantity - buyOrder.Executed
		remainingSellerQuantity := sellOrder.Quantity - sellOrder.Executed

		printOrderProcessing(buyOrder, sellOrder, processedQuantity, transactionValue, remainingBuyerQuantity, remainingSellerQuantity)

		if remainingBuyerQuantity > 0 {
			buyQueue <- buyOrder
		} else {
			queueOutput <- buyOrder
		}

		if remainingSellerQuantity > 0 {
			sellQueue <- sellOrder
		} else {
			queueOutput <- sellOrder
		}
	} else {
		buyQueue <- buyOrder
		sellQueue <- sellOrder
	}
}

func isMatchingOrder(buyOrder, sellOrder Order) bool {
	return sellOrder.Price <= buyOrder.Price
}

func determineProcessedQuantity(buyOrder, sellOrder Order) int {
	if buyOrder.Quantity-buyOrder.Executed < sellOrder.Quantity-sellOrder.Executed {
		return buyOrder.Quantity - buyOrder.Executed
	}
	return sellOrder.Quantity - sellOrder.Executed
}

func calculateTransactionValue(processedQuantity int, price float64) float64 {
	return float64(processedQuantity) * price
}

func updateOrderStatus(order *Order, processedQuantity int) {
	if order.Executed == order.Quantity {
		order.Status = "executed"
	} else if order.Executed > 0 {
		order.Status = "partially"
	}
}

func printOrderProcessing(buyOrder, sellOrder Order, processedQuantity int, transactionValue float64, remainingBuyerQuantity, remainingSellerQuantity int) {
	buyOrderJson, buyErr := json.Marshal(buyOrder)
	sellOrderJson, sellErr := json.Marshal(sellOrder)
	if buyErr != nil || sellErr != nil {
		return
	}

	fmt.Printf("============================================================================================================\n")
	fmt.Printf("Worker da %s realizou o processamento de %d ações por R$%.2f cada, totalizando R$%.2f.\n", buyOrder.StockID, processedQuantity, sellOrder.Price, transactionValue)
	fmt.Printf("------------------------------------------------------------------------------------------------------------\n")
	fmt.Printf("Compra: %s emitida com %d ações por R$%.2f cada, foi executado %d e tem pendente %d ações.\n", buyOrder.OrderID, buyOrder.Quantity, buyOrder.Price, buyOrder.Executed, remainingBuyerQuantity)
	fmt.Printf("        %s\n", string(buyOrderJson))
	fmt.Printf("------------------------------------------------------------------------------------------------------------\n")
	fmt.Printf("Venda:  %s emitida com %d ações por R$%.2f cada, foi executado %d e tem pendente %d ações.\n", sellOrder.OrderID, sellOrder.Quantity, sellOrder.Price, sellOrder.Executed, remainingSellerQuantity)
	fmt.Printf("        %s\n", string(sellOrderJson))
	fmt.Printf("============================================================================================================\n")
}

func cancelPendingOrders() {
	var wg sync.WaitGroup

	queueStock.Range(func(_, value interface{}) bool {
		orders := value.(*Stock)

		wg.Add(2)

		go func() {
			defer wg.Done()
			for len(orders.buy) > 0 {
				order := <-orders.buy
				if order.Executed == 0 {
					order.Status = "canceled"
					orderJson, err := json.Marshal(order)
					if err != nil {
						continue
					}
					log.Printf("[!] Ordem de compra cancelada: %s\n", string(orderJson))
				}
				queueOutput <- order
			}
		}()

		go func() {
			defer wg.Done()
			for len(orders.sell) > 0 {
				order := <-orders.sell
				if order.Executed == 0 {
					order.Status = "canceled"
					orderJson, err := json.Marshal(order)
					if err != nil {
						continue
					}
					log.Printf("[!] Ordem de venda cancelada:  %s\n", string(orderJson))
				}
				queueOutput <- order
			}
		}()

		return true
	})

	wg.Wait()
	close(queueOutput)
}
