module type P = sig
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
module type S = sig
  type t
  val is_generated: t -> t list -> bool
end
module Make(Prm: P) = struct
  type t = Prm.t
  module TSet = Set.Make(Prm) 
  let is_generated p g = 
    let rec generate n =
    if n=0 then (TSet.union 
                (List.fold_left (fun acc elem -> TSet.add elem acc) TSet.empty g)
                (TSet.singleton Prm.id)) 
    else
    let xn_1 = generate (n-1) in
    let xn = TSet.union xn_1 (TSet.fold (fun x acc -> TSet.add (Prm.invert x) acc) xn_1 TSet.empty) |>
              TSet.union (TSet.fold (fun x acc -> TSet.union (TSet.map (fun y-> Prm.compose x y) xn_1) acc) xn_1 xn_1) in
    if TSet.equal xn xn_1 then xn else generate (n+1) in
    TSet.mem p (generate 0)

end