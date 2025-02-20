open P
let rec echo k =
  recv (fun v ->
  send v (fun () ->
  echo k))

let rec map f pr = 
  recv (fun v ->
  send (f v) (fun () -> 
  (map f pr)))

  let rec filter p k =
    recv (fun v ->
    (if p v 
    then send v (fun () -> 
         filter p k)
    else filter p k))
  ;;
  (*
  run (filter (fun s -> String.length s >= 5))
  ;; *)
  
let rec nats_from n k =
    send n (fun () ->
    nats_from (n+1) k)
  
let sieve : ('a, 'a, int, int) proc = 
  let rec sieve cont = 
    recv (fun v ->
    send v (fun () ->
    (filter (fun x -> x mod v <> 0) >|> sieve)  cont))
  in sieve