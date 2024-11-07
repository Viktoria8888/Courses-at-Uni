(* 
para list: przed kursorem i po
jak chcemy znalezc wartosc przed kursorem, to zamiast trawersować 
calą listę, i zwracania ostatniego elementu będziemy listę
przed_kursorem trzymać w odwrotnej kolejności
 *)

type 'a zlist = 'a list * 'a list

let of_list xs = [],xs 

let to_list zs = List.rev (fst zs) @ (snd zs)

let elem zs = match (snd zs) with
  | [] -> None
  | (x :: _) -> Some(x)

let move_left zs = 
  let (f,s) = zs in
  (List.tl f, (List.hd f :: s))

let move_right zs =
  let (f,s) = zs in
  ((List.hd s) :: f, List.tl s)

let insert x zs = (x :: (fst zs)), (snd zs) 

let remove zs = List.tl (fst zs), (snd zs)

let l1 = of_list [1;2;3;4;5;6;7]

;;assert ((elem l1) = Some(1) )

let l1 = l1 |> move_right |>move_right |> move_right

;;assert ((elem l1) = Some(4))

let l1 = (insert 100 l1) |> move_left

;;assert ((elem l1) = Some(100))