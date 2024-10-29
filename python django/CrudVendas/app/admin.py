from django.contrib import admin
from .models import User, Produto, Venda

# Register your models here.

class UserAdmin(admin.ModelAdmin):
    list_display = [field.name for field in User._meta.fields]

class ProdutoAdmin(admin.ModelAdmin):
    list_display = [field.name for field in Produto._meta.fields]

class VendaAdmin(admin.ModelAdmin):
    list_display = ('id', 'produto_nome', 'vendedor_nome', 'cliente_nome', 'quantidade')

    def produto_nome(self, obj):
        return obj.produto.nome if obj.produto else "-"
    produto_nome.short_description = 'Produto'

    def vendedor_nome(self, obj):
        return obj.vendedor.nome if obj.vendedor else "-"
    vendedor_nome.short_description = 'Vendedor'

    def cliente_nome(self, obj):
        return obj.cliente.nome if obj.cliente else "-"
    cliente_nome.short_description = 'Cliente'


admin.site.register(User, UserAdmin)
admin.site.register(Produto, ProdutoAdmin)
admin.site.register(Venda, VendaAdmin)