from django.contrib.auth.models import AbstractBaseUser, BaseUserManager, PermissionsMixin
from django.db import models
from django.utils import timezone
from enum import Enum

class AreaFormacao(Enum):
    INFORMATICA = 'Informática'
    ELETROELETRONICA = 'Eletroeletrônica'
    AGROPECUARIA = 'Agropecuária'

class StatusEstagio(Enum):
    INATIVO = 'Inativo'
    ATIVO = 'Ativo'
    CONCLUIDO = 'Concluído'
    REPROVADO = 'Reprovado'

class UserType(Enum):
    ALUNO = 'Aluno'
    ORIENTADOR = 'Orientador'
    SUPERVISOR = 'Supervisor'
    ADMIN = 'Admin'

class CustomUserManager(BaseUserManager):
    def create_user(self, email, password=None, **extra_fields):
        if not email:
            raise ValueError('O endereço de e-mail deve ser fornecido')
        email = self.normalize_email(email)
        user = self.model(email=email, **extra_fields)
        user.set_password(password)
        user.save(using=self._db)
        return user

    def create_superuser(self, email, password=None, **extra_fields):
        extra_fields.setdefault('is_staff', True)
        extra_fields.setdefault('is_superuser', True)

        if extra_fields.get('is_staff') is not True:
            raise ValueError('Superusuários devem ter is_staff=True.')
        if extra_fields.get('is_superuser') is not True:
            raise ValueError('Superusuários devem ter is_superuser=True.')

        return self.create_user(email, password, **extra_fields)

class CustomUser(AbstractBaseUser, PermissionsMixin):
    email = models.EmailField(unique=True)
    nome = models.CharField(max_length=100)
    data_criacao = models.DateTimeField(default=timezone.now)

    is_active = models.BooleanField(default=True)
    is_staff = models.BooleanField(default=False)

    # Campos específicos para cada tipo de usuário
    matricula = models.CharField(max_length=20, blank=True, null=True)
    fase = models.CharField(max_length=20, blank=True, null=True)
    area_formacao = models.CharField(max_length=20, choices=[(tag, tag.value) for tag in AreaFormacao], blank=True, null=True)
    empresa = models.ForeignKey('Empresa', on_delete=models.CASCADE, related_name='supervisores', blank=True, null=True)
    user_type = models.CharField(max_length=20, choices=[(tag.value, tag.value) for tag in UserType])

    objects = CustomUserManager()

    USERNAME_FIELD = 'email'
    REQUIRED_FIELDS = ['nome']

    def __str__(self):
        return self.email

class Empresa(models.Model):
    nome = models.CharField(max_length=100)
    cnpj = models.CharField(max_length=20)
    nota = models.DecimalField(max_digits=5, decimal_places=2, default=0.0)

class Estagio(models.Model):
    aluno = models.ForeignKey(CustomUser, on_delete=models.CASCADE, related_name='estagios_aluno')
    supervisor = models.ForeignKey(CustomUser, on_delete=models.CASCADE, related_name='estagios_supervisor')
    orientador = models.ForeignKey(CustomUser, on_delete=models.CASCADE, related_name='estagios_orientador')
    avaliador = models.ForeignKey(CustomUser, on_delete=models.CASCADE, related_name='estagios_avaliador')
    empresa = models.ForeignKey(Empresa, on_delete=models.CASCADE)
    data_inicio = models.DateField()
    data_final = models.DateField()
    status = models.CharField(max_length=10, choices=[(tag, tag.value) for tag in StatusEstagio])
    relatorios = models.ManyToManyField('Relatorio', blank=True)
    atas = models.ManyToManyField('Ata', blank=True)
    banca = models.ForeignKey('Banca', on_delete=models.CASCADE)

class Banca(models.Model):
    supervisor = models.ForeignKey(CustomUser, on_delete=models.CASCADE, related_name='bancas_supervisor')
    orientador = models.ForeignKey(CustomUser, on_delete=models.CASCADE, related_name='bancas_orientador')
    aluno = models.ForeignKey(CustomUser, on_delete=models.CASCADE, related_name='bancas_aluno')
    empresa = models.ForeignKey(Empresa, on_delete=models.CASCADE)

class Ata(models.Model):
    aluno = models.ForeignKey(CustomUser, on_delete=models.CASCADE, related_name='atas_aluno')
    conteudo = models.TextField()

class Relatorio(models.Model):
    aluno = models.ForeignKey(CustomUser, on_delete=models.CASCADE, related_name='relatorios_aluno')
    conteudo = models.TextField()

class Avaliacao(models.Model):
    aluno = models.ForeignKey(CustomUser, on_delete=models.CASCADE, related_name='avaliacoes_aluno')
    empresa = models.ForeignKey(Empresa, on_delete=models.CASCADE, related_name='avaliacoes_empresa')
    nota = models.DecimalField(max_digits=5, decimal_places=2)
    comentario = models.TextField()

class Vaga(models.Model):
    nome = models.CharField(max_length=100)
    descricao = models.TextField()
    requisitos = models.TextField()
    area_formacao = models.CharField(max_length=20, choices=[(tag, tag.value) for tag in AreaFormacao])
    remunerada = models.BooleanField(default=False)
