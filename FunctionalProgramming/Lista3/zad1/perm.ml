module type OrderedType = sig
  type t (*takiego typu będzie pojedynczy element w mapie*)
  val compare : t -> t -> int
end
module type S = sig
  type key
  type t
  (** permutacja jako funkcja *)
  val apply : t -> key -> key
  (** permutacja identycznościowa *)
  val id : t
  (** permutacja odwrotna *)
  val invert : t -> t
  (** permutacja która tylko zamienia dwa elementy miejscami *)
  val swap : key -> key -> t
  (** złożenie permutacji (jako złożenie funkcji) *)
  val compose : t -> t -> t
  (** porównywanie permutacji *)
  val compare : t -> t -> int
end
module Make(Key: OrderedType) = struct
  module Tmap = Map.Make(Key)
  type key = Key.t
  type view = (key Tmap.t) * (key Tmap.t) and t = view
  
  let apply t key = match Tmap.find_opt(key) (fst t) with 
    | Some v-> v
    | None -> key 

  let id = (Tmap.empty, Tmap.empty)

  let invert t = (snd t, fst t)

  let swap k1 k2 = 
    let inv = Tmap.add k1 k2 Tmap.empty |>  Tmap.add k2 k1 in 
    (inv, inv)

  let compose t1 t2 = 
    (Tmap.merge (fun key v1 v2 ->
      match (v1, v2) with
      | (Some v1_val, Some v2_val) ->
        let new_v = apply t1 v2_val in
        if new_v = key then None else Some new_v
      | (Some v1_val, None) ->
        let new_v = v1_val in (* key=v1_val -> t2.(key) = key*)
        if new_v = key then None else Some new_v
      | (None, Some v2_val) ->
        let new_v = apply t1 v2_val in
        if new_v = key then None else Some new_v
      | (None, None) -> None
    ) (fst t1) (fst t2)),
    (Tmap.merge (fun key v1 v2 ->
      match (v1, v2) with
      | (Some v1_val, Some v2_val) ->
        let new_v = apply (invert t1) v2_val in
        if new_v = key then None else Some new_v
      | (Some v1_val, None) ->
        let new_v = v1_val in (* key=v1_val -> t2.(key) = key*)
        if new_v = key then None else Some new_v
      | (None, Some v2_val) ->
        let new_v = apply (invert t1) v2_val in
        if new_v = key then None else Some new_v
      | (None, None) -> None
    ) (fst t1) (fst t2))
    
      
  let compare t1 t2 = 
    Tmap.compare (Key.compare) (fst t1) (fst t2)
  end


(* TESTS *)
module M = Make(Int)
let id = M.id 
let swap13 = M.swap 1 3 
let swapped13 = (M.compose id swap13)
;;assert (M.apply swapped13 3 = 1)
;;assert (M.apply swapped13 1 = 3)

