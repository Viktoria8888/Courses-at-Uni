let rec sublists xs =
  match xs with
  | [] -> [[]] 
  | h :: t -> 
      let subs = sublists t in 
      subs @ (List.map (fun sub -> h :: sub) subs)


let rec suffix xs = 
  match xs with
  | [] -> [[]]
  | y :: ys -> (y :: ys) :: (suffix ys)

let rec prefix xs = List.rev_map (List.rev) (suffix (List.rev xs))