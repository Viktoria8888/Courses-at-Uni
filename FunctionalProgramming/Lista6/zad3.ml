exception FalsePredicate of string
(* let rec for_all p xs =
   try
     match xs with
     | [] -> true
     | x :: xs ->
         if not (p x) then raise (FalsePredicate "false")
         else
           (for_all p xs)
   with
     | FalsePredicate msg -> false *)

let for_all p xs =
  try
    List.fold_left
      (fun acc x -> if not (p x) then raise (FalsePredicate "false") else acc)
      true xs
  with FalsePredicate msg -> false
;;

assert (for_all (fun x -> x) [ true; true; false ] = false);;
assert (for_all (fun x -> x) [ true; true; true ] = true)

exception ZeroElement of string

let mult_list xs =
  try
    List.fold_left
      (fun acc x -> if x = 0 then raise (ZeroElement "") else x * acc)
      1 xs
  with ZeroElement msg -> 0
;;

assert (mult_list [ 1; 2; 3; 4; 5 ] = 120);;
assert (mult_list [ 1; 2; 3; 4; 5; 0 ] = 0)

exception NoOrder of string

let sorted xs =
  if (xs = []) then true else 
  try
    List.fold_left
      (fun y x -> if x < y then raise (NoOrder "") else x)
      (List.hd xs) xs;
    true
  with NoOrder msg -> false

;;assert((sorted [1;2;3;4;8;5;10]) = false)
;;assert((sorted [1;2;3;4;8;10]) = true)
;;assert((sorted []) = true)