:- ['list.pl'].

% Пункт 3
%%%%%%%%%%%%%% Поиск золовки, возвращает список девушек, подходящих устловию
find_zolovka(Ans_bag):-
	findall(D, (parent(A,X), sex(A,f), parent(B,X), sex(B,m), parent(Y,B), parent(Y,D), sex(D,f)), Ans),
	list_to_set(Ans, Ans_bag).

%%%%%%%%%%%%%% Поиск возможных решений задачи, просмотреть все можно нажатием на пробел во время исполнения
find_some_zolovka(D):-
	parent(A,X), sex(A,f),
	parent(B,X), sex(B,m),
	parent(Y,B),
	parent(Y,D), sex(D,f).

%%%%%%%%%%%%%% То же самое, просто интересный метод хранения и выведения данных
write_bag([]).
write_bag([H|T]):-
	H=[[A, A1], [B, B1], [C, C1]],
	write(A), write(A1), write('	->	'), write(B), write(B1), write(' ; '), write(C), write(C1), nl,
	write_bag(T).

find_zolovka_fun:-
	findall([['(ЗОЛОВКА) ', D], ['(МУЖ) ', B], ['(ЖЕНА) ', A]], (parent(A,X), sex(A,f), parent(B,X), sex(B,m), parent(Y,B), parent(Y,D), sex(D,f)), Ans),
	list_to_set(Ans, Ans_bag), write_bag(Ans_bag).
%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Решение знаменитой задачки: 'Сын моего отца, но не мой брат'
son_of_my_father_but_is_not_my_brother(Parent,Child,Ans):-
	parent(Parent,Child),
	parent(Parent,Ans),
	sex(Child,m),
	not(brother(Ans,Child)).

brother(Brother, Child):-
	parent(Parent,Child),
	parent(Parent,Brother),
	sex(Brother,m), Child \= Brother.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Пункт 4
link(husband, Husband, Wife):-
	parent(Husband,X),
	parent(Wife,X),
	sex(Husband,m), sex(Wife,f).

link(wife, Wife, Husband):-
	parent(Husband,X),
	parent(Wife,X),
	sex(Husband,m), sex(Wife,f).

link(brother, Brother, Y):-
	parent(X,Brother),
	parent(X,Y),
	sex(Brother,m).

link(sister, Sister, Y):-
	parent(X,Sister),
	parent(X,Y),
	sex(Sister,f).

link(father, Father, Child):-
	parent(Father,Child),
	sex(Father,m).

link(mother, Mother, Child):-
	parent(Mother,Child),
	sex(Mother,f).

link(parent, Parent, Child):-
    parent(Parent,Child).

link(son, Child, Parent):-
    parent(Parent,Child),
    sex(Child,m).

link(daughter, Child, Parent):-
	parent(Parent,Child),
	sex(Child,f).

link(child, Child, Parent):-
    parent(Parent,Child).

move(X,Y):- link(_,X,Y).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

prolong([X | T], [Y, X | T]):-
    move(X, Y),
    not(member(Y, [X | T])).

% В случае если X находится в начале очереди, получает состояние, где содержится X
bdth([[X | T] | _], X, [X | T]).
%Ищет все пути из текущего состояния и производит слияние этих путей с текущей очередью, после чего продолжает с новым состоянием в очереди
bdth([P | Q], B, R):-
    findall(X, prolong(P, X), L),
    append(Q, L, QL),
    bdth(QL, B, R), !.
% Перенаправляющее состояние, которое происходит, если не достигается конечное состояние B, то есть отправляет в хвост списка (очередь)
bdth([_ | Q], B, R):- bdth(Q, B, R).

search_bdth(X , Y, P):-
    bdth([[X]], Y, L),
    reverse(L, P).

% Получение списка имен между двумя родственниками
relative_names(X, Y, Ans):-
    search_bdth(X, Y, Ans).

% Конвертация списка имен в список типов родства между двумя соседними родственниками
transform([_], []). 
transform([A,B|T], Ans):-
    link(Rel, A, B),
    Ans = [Rel|Buf],
    transform([B|T], Buf), !.

relative_types(X, Y, Ans):-
    search_bdth(X, Y, Ans1),
    transform(Ans1, Ans).

relative(X, Y):-
	relative_names(X, Y, B),
	transform(B, A),
	write(A), nl, write(B).
