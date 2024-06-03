package ifc.sisdi.aularest.Exception;

public class ParametrosInvalidosException extends RuntimeException{
	public ParametrosInvalidosException(String fieldInvalid) {
		super("Parametros utilizados vazios ou invalidos. Parametro: " + fieldInvalid);
	}
}

