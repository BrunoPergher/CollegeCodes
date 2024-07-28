using system;
using Soccer;
var torneio = new Torneio();

Console.WriteLine("\n Bem vindos ao Futsal CUP \n");
Console.WriteLine("Regras de Funcionamento: \n");
Console.WriteLine("\n Crie os times e de a eles um nivel de habildiade de 0 a 100 \n Será feito um torneio entre eles para ver qual ficará campeão  \n");
Console.WriteLine("\n Quantos times irão disputar o campeonato: \n ");
var QuantidadeDeTimesString = Console.ReadLine();
int.TryParse(QuantidadeDeTimesString, out int QuantidadeDeTimes);

if (QuantidadeDeTimes < 2)
{
    Console.WriteLine("Para o sistema funcionar é necessesário 2 ou mais times");
    return;
}

List<Time> times = new List<Time>();

for (int i = 0; i < QuantidadeDeTimes; i++)
{
    Console.WriteLine("\n Qual o Nome do Time ?");
    var nome = Console.ReadLine();
    if (string.IsNullOrEmpty(nome))
    {
        Console.WriteLine("\n Nome Invalido! \n Qual o Nome do Time ?");
        nome = Console.ReadLine();

        if (string.IsNullOrEmpty(nome))
        {
            Console.WriteLine("Favor usar nomes validos");
            return;
        }
    }

    Console.WriteLine("\n Qual o level do time ? De 0 a 100");
    var levelString = Console.ReadLine();
    int.TryParse(levelString, out int levelInt);
    if (levelInt < 0 || levelInt > 100)
    {
        Console.WriteLine("\n Level Invalido! \n Qual o Level do Time ?");
        levelString = Console.ReadLine();
        int.TryParse(levelString, out levelInt);

        if (levelInt < 0 || levelInt > 100)
        {
            Console.WriteLine("Favor usar leveis validos");
            return;
        }
    }

    Console.WriteLine("\n Quantos Jogadores ? Minimo 5");
    var qtdJogadores = Console.ReadLine();
    int.TryParse(qtdJogadores, out int qtdJogadoresint);
    if (qtdJogadoresint < 5)
    {
        Console.WriteLine("\n Quantidade Invalido! \n Qual o numero de jogadores do Time ?");
        qtdJogadores = Console.ReadLine();
        int.TryParse(levelString, out qtdJogadoresint);

        if (qtdJogadoresint < 5)
        {
            Console.WriteLine("Favor usar leveis validos");
            return;
        }
    }


    var time = new Time { id = i, IsEliminado = false, Jogadores = qtdJogadoresint, NomeDoTime = nome, level = levelInt };
    times.Add(time);
}

while (times.Where(x => x.IsEliminado == false).Count() > 1)
{
    var timesNoCampeonato = times.Where(x => x.IsEliminado == false);
    var qtdTimesNoCampeonato = timesNoCampeonato.Count();

    if (qtdTimesNoCampeonato > 1)
    {
        var perdedor = torneio.confronto(timesNoCampeonato.First(), timesNoCampeonato.Last());
        if (qtdTimesNoCampeonato == 4)
        {
            torneio.Quarto = perdedor;
        }
        else if (qtdTimesNoCampeonato == 3)
        {
            torneio.Terceiro = perdedor;
        }
        else if (qtdTimesNoCampeonato == 2)
        {
            torneio.ViceCampeao = perdedor;
            torneio.Campeao = timesNoCampeonato.First().NomeDoTime == perdedor.NomeDoTime ? timesNoCampeonato.Last() : timesNoCampeonato.First();
        }

        if (timesNoCampeonato.First().NomeDoTime == perdedor.NomeDoTime)
        {
            timesNoCampeonato.First().IsEliminado = true;
        }
        else
        {
            timesNoCampeonato.Last().IsEliminado = true;
        }
    }
}

torneio.print();
return;