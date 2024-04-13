/* times.pl - jogo de identificação de times de futebol.

    inicia com ?- iniciar.     */

iniciar :- hipotese(Time),
      write('Eu acho que o time é: '),
      write(Time),
      nl,
      undo.

/* hipóteses a serem testadas */
hipotese(flamengo)     :- flamengo, !.
hipotese(vasco)     :- vasco, !.
hipotese(corinthians)  :- corinthians, !.
hipotese(sao_paulo)    :- sao_paulo, !.
hipotese(palmeiras)    :- palmeiras, !.
hipotese(gremio)       :- gremio, !.
hipotese(internacional) :- internacional, !.
hipotese(juventude)        :- juventude, !.
hipotese(criciuma)        :- criciuma, !.
hipotese(vitoria)        :- vitoria, !.
hipotese(bahia)        :- bahia, !.
hipotese(atletico_go)        :- atletico_go, !.
hipotese(goias)        :- goias, !.
hipotese(chapecoense)        :- chapecoense, !.
hipotese(desconhecido).             /* sem diagnóstico */

/* Regras de identificação dos times */
goias :-
    regCentroOeste,
    verificar(estado_goias),
    verificar(mascote_periquito).

atletico_go :-
    regCentroOeste,
    verificar(estado_goias),
    verificar(mascote_dragao_goiano).

bahia :-
    regNordeste,
    verificar(estado_bahia),
    verificar(mascote_home_de_aco).
    
vitoria :-
    regNordeste,
    verificar(estado_bahia),
    verificar(mascote_leao).

chapecoense :-
    regSul,
    verificar(estado_santa_catarina),
    verificar(mascote_indio).
    
criciuma :-
    regSul,
    verificar(estado_santa_catarina),
    verificar(mascote_tigre).

flamengo :-
    regSudeste,
    verificar(estado_rio_de_janeiro),
    verificar(mascote_urubu).

vasco :-
    regSudeste,
    verificar(estado_rio_de_janeiro),
    verificar(mascote_almirante).

corinthians :-
    regSudeste,
    verificar(estado_sao_paulo),
    verificar(mascote_mosqueteiro).

sao_paulo :-
    regSudeste,
    verificar(estado_sao_paulo),
    verificar(mascote_santo_paulo).

palmeiras :-
    regSudeste,
    verificar(estado_sao_paulo),
    verificar(mascote_porco).

juventude :-
    regSul,
    verificar(estado_rio_grande_do_sul),
    verificar(mascote_papagaio).

gremio :-
    regSul,
    verificar(estado_rio_grande_do_sul),
    verificar(mascote_mosqueteiro).

internacional :-
    regSul,
    verificar(estado_rio_grande_do_sul),
    verificar(mascote_saci).


 /* Regras de classificação*/
 regSudeste :- verificar(regiao_sudeste).
 regSul :- verificar(regiao_sul).
 regNordeste :- verificar(regiao_nordeste).
 regCentroOeste :- verificar(regiao_centro_Oeste).

/* Como fazer perguntas */
perguntar(Questao) :-
    write('O time possui o seguinte atributo: '),
    write(Questao),
    write(' (s|n) ? '),
    read(Resposta),
    nl,
    ((Resposta == sim ; Resposta == s) ->
       assert(yes(Questao)) ;
       assert(no(Questao)), fail).

:- dynamic yes/1,no/1.

/* Como verificar algo */
verificar(S) :-
   (yes(S)
    ->
    true ;
    (no(S)
     ->
     fail ;
     perguntar(S))).

/* Desfaz todas as afirmações sim / não */
undo :- retract(yes(_)),fail.
undo :- retract(no(_)),fail.
undo.
