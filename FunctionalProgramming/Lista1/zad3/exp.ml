(* let rec s (x:int) = (s x) *)

let hd s = s 0

let tl s = fun n -> s (n + 1)

let add s k = fun n -> k + (s n)

let map s f = fun n -> f (s n)

let map2 f s1 s2 = fun n -> f (s1 n) (s2 n)

let replace n a s = fun k -> if k = n then a else (s k)

let take_every n s = fun k -> s (k * n)

let rec nats (n:int) = (fun (x:int) -> x+1) n
  
(* hd (add nats 100);;
  hd( tl (map nats (fun x-> x*x + 500000)));;
  hd ( tl (tl (take_every 2 nats)))
*)