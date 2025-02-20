
(* Prawa równośiowe:
let* x = return e1 in e2 == let x e1 in e2 *)
(* bind (return e1) (fun x -> e2) == e2[x / e1]
 *)
(* When you combine these:

    bind (return e1) (fun x -> e2):
        return e1 wraps e1.
        bind immediately extracts e1 and passes it to the function.
    This is effectively equivalent to just substituting e1 directly into e2. *)

(* Return lewostronnym i prawostronnym elementem neutralnym *)
(* let* x = el in return x == e1 *)
(* bind e1 (fun x -> return x) == e1 *)
(* Łączność *)
(* let* x = let* y = e1 in e2 in e3 == let* y = e1 in let* x = e2 in e3 *)

(** Monada błędu -- obliczenie może się udać (konstruktor Some), albo
 * nie (konstruktor None) *)

(* Monada kontynuacyjna to jest matka wszystkich monad XD *)
module Err : sig
  type 'a t

  val return : 'a -> 'a t
  val bind   : 'a t -> ('a -> 'b t) -> 'b t

  (** Błąd *)
  val fail  : 'a t
  (** Przechwytywanie błędu *)
  val catch : 'a t -> (unit -> 'a t) -> 'a t
  
  val run : 'a t -> 'a option
end = struct
  type 'a t = 'a option

  let return x = Some x
  let bind m f =
    match m with
    | None   -> None
    | Some x -> f x

  let fail = None
  let catch m f =
    match m with
    | Some x -> Some x
    | None   -> f ()

  let run m = m
end

(** Obliczenia z nawrotami *)
module BT : sig
  type 'a t

  val return : 'a -> 'a t
  val bind   : 'a t -> ('a -> 'b t) -> 'b t

  (** Brak wyniku *)
  val fail : 'a t (*ta sćieżka obliczeń nie ma sensu*)
  (** Niedeterministyczny wybór -- zwraca true, a potem false *)
  val flip : bool t (*żeby ścieżki obliczeń się rozdzieliły*)

  val run : 'a t -> 'a Seq.t (*uruchamiamy obliczenie z nawracaniem*)
end = struct
  (* Obliczenie typu 'a to leniwa lista wszystkich możliwych wyników *)
  type 'a t = 'a Seq.t

  (* let return x = Seq.return x *)
  let return x = List.to_seq [ x ] 
  
  (* let rec bind m f () =
    match m () with
    | Seq.Nil -> Seq.Nil złożenie m na 0 sposobów
    | Cons(x, m) -> Seq.append (f x)  (bind m f) () *)
  let rec bind m f = Seq.flat_map f m

  let fail = Seq.empty
  let flip = List.to_seq [ true; false ]

  let run m = m
end

(* ========================================================================= *)
(* Przykładowy kod wykorzystujący monadę BT -- znajdowanie wszystkich trójek *)
(* pitagorejskich                                                            *)
(* ========================================================================= *)
let (let* ) = BT.bind

let rec select a b =
  if a >= b then BT.fail
  else
    let* c = BT.flip in
    if c then BT.return a
    else select (a+1) b

let triples n =
  let* a = select 1 n in
  let* b = select a n in
  let* c = select b n in
  if a*a + b*b = c*c then BT.return (a, b, c)
  else BT.fail

let x = BT.return ("hello", "world!")
let computation = 
  let* y = x in let () = print_string (fst y) in BT.return ();;  

BT.run computation ();;
(* ;;List.of_seq (BT.run (triples 50)) *)
(* ========================================================================= *)

(** Monada stanu -- obliczenia z ukrytą komórką mutowalnego stanu *)
module St(State : sig type t end) : sig
  type 'a t

  val return : 'a -> 'a t
  val bind   : 'a t -> ('a -> 'b t) -> 'b t

  (** Pobierz stan *)
  val get : State.t t
  (** Ustaw stan *)
  val set : State.t -> unit t

  val run : State.t -> 'a t -> 'a
end = struct
  (* Obliczenie reprezentujemy jako funkcję z bieżącej wartości stanu w parę
   * wynik-nowy stan *)
  type 'a t = State.t -> 'a * State.t

  (* let return x = fun st -> (x, st) *)
  let return x s = (x, s)

  (* let bind m f = fun st ->
    let (x, st) = m st in
    f x st *)
  let bind m f s =
    let (x, s) = m s in
    f x s

  (* let get st = (st, st) *)
  let get s = (s, s)
  (* let set st = fun _ -> ((), st) *)
  let set s _ = ((), s)

  let run s m = fst (m s)
end

(* Testy z wykładu *)

module IntST = St(Int)
let (let+ ) = IntST.bind

(* let foo =
  let+ x = get in
  let+ _ put (x+1) in
  if  
  
nvm  *)

let rec foo () =
  let+ x = IntST.get in
  if x = 0 then IntST.return ()
  else
    let+ _ = IntST.set (x - 1) in
    Printf.printf "%d\n" x;
    foo ()

(* IntST.run 42 (foo ()) *)
