
type _ fin_type =
  | Unit : unit fin_type
  | Bool : bool fin_type
  | Pair : 'a fin_type * 'b fin_type -> ('a * 'b) fin_type

let rec all_values: type a. a fin_type -> a Seq.t =
  fun t () ->
  match t with
    | Unit -> Seq.Cons ((), Seq.empty) 
    | Bool -> Seq.Cons (true, fun () -> Seq.Cons (false, Seq.empty))
    | Pair(p1,p2) -> let left = all_values p1 in
                     let right = all_values p2  in
                      Seq.flat_map (fun x -> Seq.map (fun y -> (x, y)) right) left ()
let l = all_values (Pair(Unit, Bool))

;;assert((List.of_seq l= [((), true); ((), false)]))