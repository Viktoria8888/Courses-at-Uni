(*-task-2-*)
type empty = |
type _ fin_type =
  | EitherT : 'a fin_type * 'b fin_type -> ('a, 'b) Either.t fin_type
  | Empty   : empty fin_type
  | Unit    : unit fin_type
  | Bool    : bool fin_type
  | Pair    : 'a fin_type * 'b fin_type -> ('a * 'b) fin_type

let rec all_values: type a. a fin_type -> a Seq.t =
  fun t () ->
  match t with
    | Empty   ->Seq.Nil
    | EitherT(p1,p2) -> let left_seq = Seq.map (fun x -> Either.Left x) (all_values p1) in
                        let right_seq = Seq.map (fun x -> Either.Right x) (all_values p2) in
                        Seq.append left_seq right_seq ()
                  
    | Unit    -> Seq.Cons ((), Seq.empty) 
    | Bool    -> Seq.Cons (true, fun () -> Seq.Cons (false, Seq.empty))
    | Pair(p1,p2) -> let left = all_values p1 in
                     let right = all_values p2  in
                     Seq.flat_map (fun x -> Seq.map (fun y -> (x, y)) right) left ()
let l  = all_values (Pair(Empty, (EitherT(Unit, Bool))))
let l1 = all_values (Pair(Bool, Empty))
let l2 = all_values (EitherT(Unit, Bool))
(* empty type will no appear in a sequence *)
let l3 = all_values (EitherT(Empty, Bool))
(* ;;assert((List.of_seq l= [((), true); ((), false)])) *)