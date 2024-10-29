(* --ex-- 4 *)
let rec merge1 cmp xs ys  = match (xs, ys) with
| ([], []) -> []
| ([], ys) -> ys
| (xs, []) -> xs
| (x:: xs, y::ys) -> 
  if (cmp x y) then x :: (merge1  cmp xs (y::ys))
  else y :: (merge1 cmp (x :: xs) ys)

(* tail recursion *)
(* let rec merge_tail cmp xs ys acc = match (xs, ys) with
| ([], []) -> acc
| ([], ys) -> acc @ ys
| (xs, []) -> acc @ xs
| (x:: xs, y::ys) -> 
  if (cmp x y) then merge_tail cmp xs (y::ys) (acc @ [x]) 
  else merge_tail cmp (x::xs)  ys (acc @ [y]) *)

let merge_tail_rev cmp xs ys = 
  let rec it cmp xs ys acc =
    match (xs, ys) with
    | ([],[]) -> List.rev acc
    | ([],y::ys)->  (it cmp xs ys (y::acc))
    | (x::xs, [])->  (it cmp xs ys (x::acc))
    | (x:: xs, y::ys) -> 
      if (cmp x y) then it cmp xs (y::ys) (x::acc)
      else it cmp (x::xs) ys (y::acc)
  in it cmp xs ys []


(* halve *)
let rec halve xs = match xs with
  | [] -> ([], [])
  | x :: [] -> ([x], [])
  | x :: y :: xs -> let (x1, x2) = halve xs in (x :: x1, y :: x2)

(* mergesort *)

let rec mergesort cmp xs mergeFun = match xs with
  | [] -> []
  | [x] ->[x]
  | x :: xs -> let (x1, x2) = halve (x::xs) in 
  (mergeFun cmp (mergesort cmp x1 mergeFun) (mergesort cmp x2 mergeFun))

(* TESTS *)
let list1 = (List.init 1000 (fun x-> x * (-1)))
;;assert ((mergesort (<=) [5;4;3;2;1] merge1) = [1;2;3;4;5])
;;assert ( mergesort (<=) list1 merge_tail_rev = List.sort Int.compare list1)

  

(* --ex-- 5 *)
let merge_tail cmp xs ys = 
  let rec it cmp xs ys acc =
    match (xs, ys) with
    | ([],[]) -> acc
    | ([],y::ys)->  (it cmp xs ys (y::acc))
    | (x::xs, [])->  (it cmp xs ys (x::acc))
    | (x:: xs, y::ys) -> 
      if (cmp x y) then it cmp xs (y::ys) (x::acc)
      else it cmp (x::xs) ys (y::acc)
  in it cmp xs ys []


let rec mergesort_tail cmp xs= match xs with
  | [] -> []
  | [x] ->[x]
  | x::xs-> let (x1, x2) =  halve (x::xs) in
      (merge_tail (fun x y -> not (cmp x y))
      (mergesort_tail (fun x y -> not (cmp x y)) x1)
      (mergesort_tail (fun x y -> not (cmp x y)) x2))

let time1 f cmp xs m =
  let t = Sys.time() in
    let _ = f cmp xs m in
      Printf.printf "Execution time with reverse: %fs\n" (Sys.time() -. t)

let time2 f cmp xs =
  let t = Sys.time() in
    let _ = f cmp xs in
      Printf.printf "Execution time of merging without reverse: %fs\n" (Sys.time() -. t)
(* Trzeba najpierw skompilowac, a potem sprawdzac predkosc *)
(*-TESTS-*)
;;assert ( mergesort_tail (<=) list1 = List.sort Int.compare list1)
;; time2 mergesort_tail (<=) list1 

;; time1 mergesort (<=) list1 merge_tail_rev

