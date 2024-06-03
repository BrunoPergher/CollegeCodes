package ifc.sisdi.aularest.Controllers;

import java.util.concurrent.atomic.AtomicInteger;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import ifc.sisdi.aularest.Models.*;

@RestController
public class SaudacaoController {
	private static final String MENSAGEM = "Ol´a %s";
	private AtomicInteger contador = new AtomicInteger();
	@GetMapping("/saudacao")
	public Saudacao saudacao(@RequestParam(value = "nome", defaultValue = "mundo") String nome)
	{
		return new Saudacao(this.contador.incrementAndGet(), String.format(MENSAGEM, nome));
	}
}
