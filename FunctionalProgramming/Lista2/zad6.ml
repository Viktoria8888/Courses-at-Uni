
(* using insertion *)
let rec insert_all_positions x ys =
  match ys with
  | [] -> [[x]]  
  | y :: ys' -> 
      (x :: ys) :: List.map (fun zs -> y :: zs) (insert_all_positions x ys')
let rec permutation1 xs = 
  match xs with
  | [] -> [[]]  
  | x :: xs -> 
      let perms_of_xs = permutation1 xs in   
      List.concat (List.map (insert_all_positions x) perms_of_xs)

(* using selection *)
(* remove the element-> generate all the permutatioin for the rest of the list
-> insert the removed element on the first place*)
let rec rm y xs = match xs with
| [] -> []
| x :: xs -> if x=y then rm y xs else x:: (rm y xs)
;;assert (rm 10 [2;3;10;4;1] = [2; 3; 4; 1])

let rec permutation2 xs = match xs with
  | [] -> [[]]
  | ys ->  List.concat (List.map (fun x-> 
                                  List.map (fun zs -> x :: zs) 
                                           (permutation2 (rm x ys))) ys)
;;assert ( (permutation1 [1;2;3]) =   [[1; 2; 3]; [2; 1; 3]; [2; 3; 1]; [1; 3; 2]; [3; 1; 2]; [3; 2; 1]])
;;assert ( (permutation2 [1;2;3]) =  [[1; 2; 3]; [1; 3; 2]; [2; 1; 3]; [2; 3; 1]; [3; 1; 2]; [3; 2; 1]])
