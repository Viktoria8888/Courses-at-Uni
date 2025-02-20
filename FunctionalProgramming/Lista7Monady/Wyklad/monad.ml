module Err : sig
  type 'a t

  val return : 'a -> 'a t
  val bind : 'a t -> ('a -> 'b t) -> 'b t

  val fail : 'a t

  val catch : 'a t -> (unit -> 'a t) -> 'a t

  val run : 'a t -> 'a option
end = struct
  type 'a t = 'a option

  let return x = Some x
  let bind m f =
    match m with
    | Some x -> f x
    | None   -> None

  let fail = None

  let catch m f =
    match m with
    | Some x -> Some x
    | None   -> f ()

  let run m = m
end

module BT : sig
  type 'a t

  val return : 'a -> 'a t
  val bind : 'a t -> ('a -> 'b t) -> 'b t
  
  val fail : 'a t
  val flip : bool t

  val run : 'a t -> 'a Seq.t
end = struct
  type 'a t = 'a Seq.t

  let return x = List.to_seq [x]
  let bind m f = Seq.flat_map f m

  let fail = Seq.empty
  let flip = List.to_seq [true; false]

  let run m = m
end

module ST(S : sig type t end) : sig
  type 'a t

  val return : 'a -> 'a t
  val bind : 'a t -> ('a -> 'b t) -> 'b t

  val get : S.t t
  val put : S.t -> unit t

  val run : S.t -> 'a t -> 'a
end = struct
  type 'a t = S.t -> 'a * S.t

  let return x = fun st -> (x, st)
  let bind m f = fun st ->
    let (x, st) = m st in
    f x st

  let get st = (st, st)
  let put st = fun _ -> ((), st)

  let run st m = fst (m st)
end

let (let* ) = BT.bind

let rec select a b =
  if a >= b then BT.fail
  else
    let* x = BT.flip in
    if x then BT.return a
    else select (a+1) b

let triples n =
  let* a = select 1 n in
  let* b = select a n in
  let* c = select b n in
  if a*a + b*b = c*c then BT.return (a, b, c)
  else BT.fail

module IntST = ST(Int)
let (let+ ) = IntST.bind

let rec foo () =
  let+ x = IntST.get in
  if x = 0 then IntST.return ()
  else
    let+ _ = IntST.put (x - 1) in
    Printf.printf "%d\n" x;
    foo ()
