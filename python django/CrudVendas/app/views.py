from django.shortcuts import render

# Create your views here.
from .models import Venda
from .models import Produto
from .models import User
import matplotlib
matplotlib.use('Agg')  # Use o modo "Agg" para renderização sem GUI
import matplotlib.pyplot as plt
from io import BytesIO
import base64
from django.db.models import Sum, Count

def vendas(request):
    vendas = Venda.objects.all()
    return render(request, 'vendas.html', {'vendas': vendas})

def users(request):
    users = User.objects.all()
    return render(request, 'users.html', {'users': users})

def produtos(request):
    produtos = Produto.objects.all()
    return render(request, 'produtos.html', {'produtos': produtos})

def dashboard(request):
   # Quantidade de vendedores
    vendedores = User.objects.filter(isVendedor=True).count()

    # Quantidade de vendas
    quantidade_vendas = Venda.objects.count()

    # Quantidade de usuários que não são vendedores
    nao_vendedores = User.objects.filter(isVendedor=False).count()

    # Valor total adquirido através das vendas
    valor_total_vendas = Venda.objects.aggregate(soma_vendas=Sum('produto__valor'))['soma_vendas']

    # Criar gráfico para vendedores
    fig_vendedores, ax_vendedores = plt.subplots(figsize=(8, 5))
    ax_vendedores.bar(['Vendedores', 'Não Vendedores'], [vendedores, nao_vendedores], color='skyblue')
    ax_vendedores.set_ylabel('Quantidade')
    ax_vendedores.set_title('Vendedores vs. Não Vendedores')

    # Adicionar valores acima das barras no gráfico de vendedores
    for i, v in enumerate([vendedores, nao_vendedores]):
        ax_vendedores.text(i, v + 2, str(v), ha='center', va='bottom', fontsize=12)

    # Criar gráfico para vendas
    fig_vendas, ax_vendas = plt.subplots(figsize=(8, 5))
    ax_vendas.bar(['Quantidade de Vendas', 'Valor Total (R$)'], [quantidade_vendas, valor_total_vendas], color='lightcoral')
    ax_vendas.set_ylabel('Quantidade/Valor')
    ax_vendas.set_title('Estatísticas de Vendas')

    # Adicionar valores acima das barras no gráfico de vendas
    for i, v in enumerate([quantidade_vendas, valor_total_vendas]):
        ax_vendas.text(i, v + 2, str(v), ha='center', va='bottom', fontsize=12)

    # Quantidade total de produtos
    total_produtos = Produto.objects.count()

    # Quantidade de produtos com estoque baixo
    produtos_estoque_baixo = Produto.objects.filter(estoque__lt=10).count()

    # Criar gráfico para estoque de produtos
    fig_estoque, ax_estoque = plt.subplots(figsize=(8, 5))
    ax_estoque.bar(['Total de Produtos', 'Produtos com Estoque Baixo'], [total_produtos, produtos_estoque_baixo], color='lightcoral')
    ax_estoque.set_ylabel('Quantidade')
    ax_estoque.set_title('Estoque de Produtos')

    # Adicionar valores acima das barras no gráfico de estoque
    for i, v in enumerate([total_produtos, produtos_estoque_baixo]):
        ax_estoque.text(i, v + 2, str(v), ha='center', va='bottom', fontsize=12)

    # Calcular os produtos mais vendidos
    produtos_mais_vendidos = (
        Venda.objects.values('produto__nome')
        .annotate(total_vendas=Count('produto__nome'))
        .order_by('-total_vendas')[:5]  # Obtém os 5 produtos mais vendidos
    )

    nomes_produtos_mais_vendidos = [produto['produto__nome'] for produto in produtos_mais_vendidos]
    total_vendas_produtos_mais_vendidos = [produto['total_vendas'] for produto in produtos_mais_vendidos]

    # Criar gráfico de pizza para os produtos mais vendidos
    fig_produtos_mais_vendidos, ax_produtos_mais_vendidos = plt.subplots(figsize=(8, 8))
    ax_produtos_mais_vendidos.pie(total_vendas_produtos_mais_vendidos, labels=nomes_produtos_mais_vendidos, autopct='%1.1f%%', startangle=140)
    ax_produtos_mais_vendidos.axis('equal')  # Equal aspect ratio ensures that pie is drawn as a circle.
    ax_produtos_mais_vendidos.set_title('Produtos Mais Vendidos')

    # Salvar os gráficos em imagens separadas
    buffer_vendedores = BytesIO()
    plt.figure(fig_vendedores.number)
    plt.savefig(buffer_vendedores, format='png')
    buffer_vendedores.seek(0)
    image_png_vendedores = buffer_vendedores.getvalue()
    buffer_vendedores.close()

    buffer_vendas = BytesIO()
    plt.figure(fig_vendas.number)
    plt.savefig(buffer_vendas, format='png')
    buffer_vendas.seek(0)
    image_png_vendas = buffer_vendas.getvalue()
    buffer_vendas.close()

    buffer_estoque = BytesIO()
    plt.figure(fig_estoque.number)
    plt.savefig(buffer_estoque, format='png')
    buffer_estoque.seek(0)
    image_png_estoque = buffer_estoque.getvalue()
    buffer_estoque.close()

    buffer_produtos_mais_vendidos = BytesIO()
    plt.figure(fig_produtos_mais_vendidos.number)
    plt.savefig(buffer_produtos_mais_vendidos, format='png')
    buffer_produtos_mais_vendidos.seek(0)
    image_png_produtos_mais_vendidos = buffer_produtos_mais_vendidos.getvalue()
    buffer_produtos_mais_vendidos.close()

    # Codificar as imagens em base64
    graphic_vendedores = base64.b64encode(image_png_vendedores).decode()
    graphic_vendas = base64.b64encode(image_png_vendas).decode()
    graphic_estoque = base64.b64encode(image_png_estoque).decode()
    graphic_produtos_mais_vendidos = base64.b64encode(image_png_produtos_mais_vendidos).decode()

    return render(request, 'dashboards.html', {
        'graphic_vendedores': graphic_vendedores,
        'graphic_vendas': graphic_vendas,
        'graphic_estoque': graphic_estoque,
        'graphic_produtos_mais_vendidos': graphic_produtos_mais_vendidos,
    })