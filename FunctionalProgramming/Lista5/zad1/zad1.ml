let rec fix f x = f (fix f) x

let fib_f fib n =
  if n <= 1 then n
  else fib (n-1) + fib (n-2)

let rec fix_with_limit n f x = if (n < 0) then failwith "recursion depth exceeded" else f (fix_with_limit (n-1) f) x


let fib1 = fix_with_limit 10 fib_f

(* ;;fib1 20 *)
(* problem: one hashtable is shared among all the invocations of fix_mem *)
let tab = Hashtbl.create 100000
let rec fix_memo f x =
  match Hashtbl.find_opt tab x with
    | Some(y) -> y
    | None -> let v = f (fix_memo f) x in
              let _ = Hashtbl.add tab x v in v
let fib2 = fix_memo fib_f


let fix_memo1 f x =
  let cache = Hashtbl.create 100000 in   
  let rec aux f x =
    match Hashtbl.find_opt cache x with
    | Some(y) -> y
    | None -> let v = f (aux f) x in
              let _ = Hashtbl.add cache x v in v
    in (aux f x)
    	
    
let fib2 = fix_memo fib_f
let fib3 = fix_memo1 fib_f 
;;assert (fib3 60 = fib2 60);
;;assert (fib2 60 = 1548008755920);
