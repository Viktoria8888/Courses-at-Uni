let length xs = List.fold_left (fun acc x -> acc+1) 0 xs

let rev xs = List.fold_left (fun acc x -> x :: acc) [] xs 
(* (cons 2 (сons 1 [])) *)
let map xs f  = List.fold_right (fun x acc -> ( f x) :: acc) xs []

let append xs x = List.fold_right (fun y acc ->  y:: acc) xs [x];;
(* (cons 3 (cons 4 [x])) *)
let rev_append xs ys =
 List.fold_left (fun acc y -> y :: acc) ys xs 
 (* List.rev [1;2;3]  @  [41;42];; *)
(* (cons 2 ( cons 1 [x]) ) -> rev x ,1 ,2, 3 ,4 ) *)

let filter xs p = let res = List.fold_left (fun acc x -> if (p x) then x::acc else []) [] xs in (rev res);;

let rev_map xs f = List.fold_left (fun acc x ->  (f x) :: acc) [] xs 
let xs = [1;2;3;4]
(* (cons 3 (cons 2 (cons 1 [])))  *)