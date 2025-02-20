(* copilot: disable *)
module BT : sig
  type 'a t

  val return : 'a -> 'a t
  val bind   : 'a t -> ('a -> 'b t) -> 'b t

  (** Brak wyniku *)
  val fail : 'a t (*ta sćieżka obliczeń nie ma sensu*)
  (** Niedeterministyczny wybór -- zwraca true, a potem false *)
  val flip : bool t (*żeby ścieżki obliczeń się rozdzieliły*)

  val run : 'a t -> 'a Seq.t (*uruchamiamy obliczenie z nawracaniem*)
end = struct
  (* Obliczenie typu 'a to leniwa lista wszystkich możliwych wyników *)
  type 'a t = 'a Seq.t

  (* let return x = Seq.return x *)
  let return x = List.to_seq [ x ] 
  
  (* let rec bind m f () =
    match m () with
    | Seq.Nil -> Seq.Nil złożenie m na 0 sposobów
    | Cons(x, m) -> Seq.append (f x)  (bind m f) () *)
  let rec bind m f = Seq.flat_map f m

  let fail = Seq.empty
  let flip = List.to_seq [ true; false ]

  let run m = m
end
let (let*) = BT.bind 
let is_valid r c placements = 
  List.for_all (fun (r',c') -> r' <> r && c <> c' && abs(r-r') <> abs(c-c')) placements


let rec dfs r n curr_placement = 
  if r = n then BT.return curr_placement
  else
    let rec try_col c placement  = 
      if c=n then BT.fail else
      let* valid_toss = BT.flip in
        if (valid_toss && (is_valid r c placement)) then
        let* solution = dfs (r + 1) n ((r,c) :: placement) in
        BT.return solution
      else try_col (c + 1) placement
    in
    let* res = try_col 0 curr_placement in
    BT.return res


let nqueens n = dfs 0 n []
let is_empty seq = match seq () with
    | Seq.Nil-> true
    | Seq.Cons _ -> false
(* let placement_exists n =  *)
let exists_nqueens n = BT.run (nqueens n) |> is_empty |> not

