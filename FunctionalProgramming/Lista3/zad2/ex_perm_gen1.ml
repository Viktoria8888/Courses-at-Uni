module P = Perm.Make(Int);;
(* module P :
  sig
    type key = int
    type t = Perm.Make(Int).t
    val apply : t -> key -> key
    val id : t
    val invert : t -> t
    val swap : key -> key -> t
    val compose : t -> t -> t
    val compare : t -> t -> key
  end *)
module G = Gen.Make(P);;
(* module G : sig type t = P.t val is_generated : t -> t list -> bool end *)
let id = P.id;;
(* val id : G.t = <abstr> *)
let swap13 = P.swap 1 3;;
(* val swap13 : G.t = <abstr> *)
(* let swapped13 = P.compose id swap;; *)
(* Error: Unbound value swap *)
let swapped13 = P.compose id swap13;;
(* val swapped13 : G.t = <abstr> *)
(* let g = [id;swapped];; *)
(* Error: Unbound value swapped
Hint: Did you mean swapped13? *)
let g = [id;swapped13];;
(* val g : G.t list = [<abstr>; <abstr>] *)
let g = [id; swap13];;
(* val g : G.t list = [<abstr>; <abstr>] *)
G.is_generated swapped13 g;;
(* - : bool = true *)
#utop_save;;
(* Directive `utop_save' expects a `string' literal, got no argument. *)
#utop_save "ex_perm_gen";;
#utop_stash "ex_perm_gen1";;






