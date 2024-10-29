type cbool = {cbool: 'a. 'a->'a->'a}

(* Modyfikacja zadania 6 *)

let ctrue = {cbool = fun a b -> if true then a else b}
let cfalse = {cbool = fun a b->if false then a else b}

let cand f g = {cbool = fun a b -> if (f.cbool a b) = a && (g.cbool a b) = a then a else b}
let cor f g = {cbool = fun a b -> if (f.cbool a b) = a || (g.cbool a b) =a then a else b}
let cbool_of_bool v = if v then ctrue else cfalse

let bool_of_cbool v = if (v.cbool true false) then true else false

(* (bool_of_cbool {cbool = (+)});; *)

type cnum = { cnum : 'a. ('a -> 'a) -> 'a -> 'a }

let zero = {cnum= fun f x->
  if true then x
  else (f x)}

let succ fn = {cnum = fun f x-> f ( fn.cnum f x)}

(*add && mul*)
let add fn fk = {cnum = fun f x -> (fn.cnum f (fk.cnum f x))}
(*f^{n+k}(x) = f^{n}(f^{k}(x))*)
let mul fn fk = {cnum = fun f x -> (fn.cnum (fk.cnum f) x)}
(*f^{n*k}(x) = (f^{k})^{n}(x) = (f^k(...(f^k(f^k)...)(x) - to n razy*)
(*is_zero*)

let one = (succ zero)
let two = (succ (succ zero))
let three = (succ (succ (succ zero)))

let is_zero num = 
  {cbool= (fun a b ->
    if (num.cnum (fun x -> if true then b else x) a) == a then a
    else b)}

let rec cnum_of_int n =
  if n == 0 then zero else {cnum = fun f x -> 
                                    f ((cnum_of_int(n-1)).cnum f x)}

let int_of_cnum cn = 
    (cn.cnum (fun x -> x+1) 0)