package ifc.sisdi.aularest.Controllers;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

import ifc.sisdi.aularest.Exception.*;
import ifc.sisdi.aularest.Models.*;

@RestController
@RequestMapping("/pessoas")
public class AgendaController {
	private List<Pessoa> agenda = new ArrayList<>();
	private AtomicInteger contador = new AtomicInteger();

	@GetMapping
	public List<Pessoa> obterTodasPessoas(){
		return this.agenda;
	}

	@GetMapping("/{id}")
	public Pessoa obterPessoa(@PathVariable int id) {
		for (Pessoa p : this.agenda) {
			if (p.getId() == id)
				return p;
		}

		throw new PessoaNaoEncontradaException(id);
	}

	@PostMapping
	@ResponseStatus(HttpStatus.CREATED)
	public Pessoa adicionarPessoa(@RequestBody Pessoa p) {
		if(p.getNome() == "") {
			throw new ParametrosInvalidosException("Nome is invalid");
		} else if( p.getEmail() == "") {
			throw new ParametrosInvalidosException("Email is invalid");
		}

		p.setId(this.contador.incrementAndGet());
		this.agenda.add(p);

		return p;
	}

	@PutMapping("/{id}")
	public Pessoa atualizarPessoa(@RequestBody Pessoa p, @PathVariable int id) {
		for (Pessoa pessoa: this.agenda) {
			if(p.getNome() == "") {
				throw new ParametrosInvalidosException("Nome is invalid");
			} else if( p.getEmail() == "") {
				throw new ParametrosInvalidosException("Email is invalid");
			}

			if (pessoa.getId() == id) {
				pessoa.setEmail(p.getEmail());
				pessoa.setNome(p.getNome());
				return pessoa;
			}
		}
		
		throw new PessoaNaoEncontradaException(id);
	}

	@DeleteMapping("/{id}")
	public int excluirPessoa(@PathVariable int id) {
		for(Pessoa p: this.agenda) {
			if (p.getId() == id) {
				this.agenda.remove(p);
				return id;
			}
		}
		
		throw new PessoaNaoEncontradaException(id);
	}

	@ControllerAdvice
	class PessoaNaoEncontrada {
		@ResponseBody
		@ExceptionHandler(Exception.class)
		@ResponseStatus(HttpStatus.NOT_FOUND)
		String pessoaNaoEncontrada(PessoaNaoEncontradaException p){
			return p.getMessage();
		}
	}
	
	@ControllerAdvice
	class ParametroInvalido {
		@ResponseBody
		@ExceptionHandler(ParametrosInvalidosException.class)
		@ResponseStatus(HttpStatus.BAD_REQUEST)
		String parametroInvalido(ParametrosInvalidosException p){
			return p.getMessage();
		}
	}
}