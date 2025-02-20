let rec fold_left_cps (f : ('a -> 'b -> ('a -> 'c) -> 'c)) (acc : 'a) (xs : 'b list) (cnt : 'a -> 'c) : 'c = 
  match xs with
  | [] -> cnt acc
  | x :: xs ->  f acc x (fun new_acc -> fold_left_cps f new_acc xs cnt)
 

let for_all p xs = fold_left_cps (fun acc x cnt ->
    if (p x) then (cnt acc) else false) true xs Fun.id
  

;;assert (for_all (fun x -> x) [ true; true; false ] = false);;
assert (for_all (fun x -> x) [ true; true; true ] = true)

let mult_list xs = fold_left_cps (fun acc x cnt ->
if (x!=0) then (cnt x*acc) else 0) 1 xs Fun.id

;;assert (mult_list [ 1; 2; 3; 4; 5 ] = 120);;
assert (mult_list [ 1; 2; 3; 4; 5; 0 ] = 0)

(* let sorted xs = if (xs = []) then false else
  fold_left_cps (fun acc x cnt ->
  if (x<acc) then (cnt x) else (fun y -> false)) (List.hd xs) xs (fun y -> true) *)

let sorted xs = if (xs = []) then true else snd (fold_left_cps (fun acc x cnt -> 
  let (y, b) = acc in
  if (x >= y) then (cnt (x, true)) else (0,false)) (List.hd xs,true) xs  Fun.id)

;;assert((sorted [1;2;3;4;8;5;10]) = false)
;;assert((sorted [1;2;3;4;8;10]) = true)
;;assert((sorted []) = true)