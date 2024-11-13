let rec fix f x = f (fix f) x

let fix_m f =
  let x = ref (fun _ -> failwith "empty") in
  x := f (fun y -> !x y);
  !x  

let fib_f fib n =
  if n <= 1 then n
  else fib (n-1) + fib (n-2)

let fib = fix_m fib_f

(*
let fix f z =(fun x z -> f (x x) z) (fun x z -> f (x x) z) z;;
Error: This expression has type 'a -> 'b but an expression was expected of type 'a
The type variable 'a occurs inside 'a -> 'b *)

type 'a recursive = In of ('a recursive -> 'a)
let out (In arrec) = arrec
let fix_t f = (fun x a -> f (out x x) a) (In (fun x a -> f (out x x) a))

let fib2 = fix_t fib_f