package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type Task struct {
	id       int
	producer int
}

func producer(id int, taskQueue chan<- Task, stopChan <-chan bool, wg *sync.WaitGroup, producerDelay time.Duration) {
	defer wg.Done()
	for {
		select {
		case <-stopChan:
			return
		default:
			startTime := time.Now()
			time.Sleep(time.Duration(rand.Intn(int(producerDelay.Seconds()))+1) * time.Second)
			creationTime := time.Since(startTime)

			task := Task{
				id:       rand.Intn(1000),
				producer: id,
			}

			taskQueue <- task

			fmt.Printf("[?] Produtor %d criou a tarefa %d em %v\n", id, task.id, creationTime)
		}
	}
}

func consumer(id int, taskQueue <-chan Task, wg *sync.WaitGroup, consumerDelay time.Duration) {
	defer wg.Done()
	for task := range taskQueue {
		randomDelay := time.Duration(rand.Intn(int(consumerDelay.Seconds()))+1) * time.Second
		fmt.Printf("[#] Consumidor %d está processando a tarefa %d produzido pelo %d\n", id, task.id, task.producer)
		time.Sleep(randomDelay)
		fmt.Printf("[!] Consumidor %d completou a tarefa %d produzido pelo %d em %v\n", id, task.id, task.producer, randomDelay)
	}
}

func main() {
	producerDelay := 5 * time.Second
	consumerDelay := 10 * time.Second
	totalProducers := 100
	totalConsumers := 10
	totalTime := 10 * time.Second
	lengthQueue := 1000

	taskQueue := make(chan Task, lengthQueue)
	stopChan := make(chan bool)
	var wgProducers sync.WaitGroup
	var wgConsumers sync.WaitGroup

	for i := 0; i < totalProducers; i++ {
		wgProducers.Add(1)
		go producer(i+1, taskQueue, stopChan, &wgProducers, producerDelay)
	}

	for i := 0; i < totalConsumers; i++ {
		wgConsumers.Add(1)
		go consumer(i+1, taskQueue, &wgConsumers, consumerDelay)
	}

	time.Sleep(totalTime)
	close(stopChan)

	wgProducers.Wait()

	close(taskQueue)

	wgConsumers.Wait()

	fmt.Println("Todos os produtores e consumidores finalizaram.")
}
