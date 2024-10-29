(*zero && succ*) (*ZLE*)
(* let zero f = fun x-> (f x) *)

let zero f x =
  if true then x
  else (f x)

let succ fn f = fun x-> f ( fn f x)

(*add && mul*)
let add fn fk = fun f x -> (fn f (fk f x))
(*f^{n+k}(x) = f^{n}(f^{k}(x))*)
let mul fn fk = fun f x -> (fn (fk f) x)
(*f^{n*k}(x) = (f^{k})^{n}(x) = (f^k(...(f^k(f^k)...)(x) - to n razy*)
(*is_zero*)

let one = (succ zero)
let two = (succ (succ zero))
let three = (succ (succ (succ zero)))
(* add two one (fun x-> x+1) 0;; *)


let ctrue a b = if true then a else b
let cfalse a b = if true then b else a
let cand f g = fun a b -> if (f a b) = a && (g a b) = a then a else b;;
let cor f g = fun a b -> if (f a b) = a || (g a b) =a then a else b;;
let cbool_of_bool v = if v then ctrue else cfalse
let  bool_of_cbool v = if (v true false) then true else false;

(* let is_zero num = 
  (fun a b ->
    if (num (fun x -> if true then b else x) a) == a then a
    else b)

let rec cnum_of_int n =
  if n == 0 then zero else (fun f x ->(f (cnum_of_int (n-1) f x)))

let int_of_cnum cn = 
    (cn (fun x -> x+1) 0) *)
