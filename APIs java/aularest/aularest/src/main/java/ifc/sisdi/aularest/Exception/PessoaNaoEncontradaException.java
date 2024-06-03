package ifc.sisdi.aularest.Exception;

public class PessoaNaoEncontradaException extends RuntimeException{
	public PessoaNaoEncontradaException(int id) {
		super("N~ao foi poss´ıvel encontrar pessoa com o id: " + id);
	}
}

