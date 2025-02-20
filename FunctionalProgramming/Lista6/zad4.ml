let rec fold_left_cps (f : ('a -> 'b -> ('a -> 'c) -> 'c)) (acc : 'a) (xs : 'b list) (cnt : 'a -> 'c) : 'c = 
  match xs with
  | [] -> cnt acc
  | x :: xs ->  f acc x (fun new_acc -> fold_left_cps f new_acc xs cnt)
 