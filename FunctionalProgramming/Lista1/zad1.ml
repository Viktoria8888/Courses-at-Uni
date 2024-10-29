(* Typ wyrażenia jest 'a->'a*)
let f x = x
let f1 x = (f x) + 1 (* int->int*)

(*(’a -> ’b) -> (’c -> ’a) -> ’c -> ’b*)
let f2 f g  x = f (g x)

(*’a -> ’b -> ’a*)
let f3 x f = x

(*a -> ’a -> ’a*)

 (* let f3 (x:'a) (y:'a) = x; *)
 let f3 x y = if x=y then x else y

