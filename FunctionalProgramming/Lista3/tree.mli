module type OrderedType = sig 
    type t
    val compare : t -> t -> int
end
  (* aliasy typu *)
module type S = sig
  type elt  (*typ abstrakcyjny, nie ujawniamy jego implementacji*)
  type t

  type view =
    | Leaf
    | Node of t * elt * t

  val view : t -> view

  val empty : t

  val add : t -> elt -> t

  val mem : t -> elt -> bool
end
  
module Make(Elt : OrderedType) : S with type elt = Elt.t
(* typy zalezne; sygnatury nie mogą być sprarametryzowane*)