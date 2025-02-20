module type Monad = sig
  type 'a t
  val return : 'a -> 'a t
  val bind : 'a t -> ('a -> 'b t) -> 'b t
end
module Err : sig
  include Monad
  val fail : 'a t
  val catch : 'a t -> (unit -> 'a t) -> 'a t
  val run : 'a t -> 'a option
end=struct

  type 'r ans = 'r option
  type 'a t = { run : ('a -> 'a ans) -> 'a ans }

  let return x = {run = fun cont -> cont x }
  let bind m f = {run = fun cont -> m.run (fun x -> 
                                    (f x).run
                                    cont)}

  (* let bind m f = {run = fun cont -> match m.run (fun x -> Some x) with
                                    | None -> None
                                    | Some x -> (f x).run cont } *)
(* 
  let bind m f = {run = fun cont -> match m.run (fun x -> (f x).run cont) with
                                    | None -> None
                                    | Some x -> Some x } *)
  let fail = {run= (fun _ -> None)}

  let catch m f = {run = fun cont -> match m.run (fun x -> Some x) with
                                    | None -> (f ()).run cont
                                    | Some x -> cont x}
  let run m = m.run (fun x -> Some x )
 
end



module BT : sig
  include Monad
  val fail : 'a t
  val flip : bool t
  val run : 'a t -> 'a Seq.t
end = struct
  type 'r ans = 'r Seq.t
  type 'a t = { run : ('a -> 'a ans) -> 'a ans }

  let return x = {run = fun cont -> cont x}
  let bind m f = {run = fun cont -> m.run (fun x -> 
                                    (f x).run
                                    cont)}
  (* let bind m f = {run = fun cont -> Seq.flat_map 
                                    (fun x -> 
                                    (f x).run
                                    cont)
                                    (m.run (fun x -> List.to_seq [x]))} *)
  let fail = {run = fun cont -> Seq.empty}
  let flip = {run = fun cont -> Seq.flat_map cont (List.to_seq [false; true])} 
  let run m = m.run (fun x -> List.to_seq [x])
  
end

module St(State : sig type t end) : sig
  include Monad
  val get : State.t t
  val set : State.t -> unit t
  val run : State.t -> 'a t -> 'a
end = struct
  type 'r ans = State.t -> 'r * State.t
  type 'a t = { run : 'r. ('a -> 'r ans) -> 'r ans }

  let return x = { run = fun cont -> cont x }

  let bind m f = {run = fun cont -> m.run (fun x -> 
                                    (f x).run
                                    cont)}

  let get = { run = fun cont -> 
    fun s -> (cont s) s}

  let set s_new = { run = fun cont ->
    fun s_prev -> (cont ()) s_new}

  let run s m = fst ((m.run (fun x -> fun s -> (x, s))) s)
  (* let run s m = 
    fst (m.run (fun x s -> (x, s)) s) *)
end
(* 
// stan poczatkowy            10
let* res = get + 2 in  // 12, 10
let* _ = set 20 in     // (), 20
get + 2                // 22, 20 *)
(* 
// s
let* x = .... in
x = x *)
