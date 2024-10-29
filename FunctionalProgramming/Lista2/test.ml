open Heap

let rec tolist h =
  if h = empty then []
  else match minheap h with
    | None -> []  
    | Some min_value -> 
        min_value :: tolist (erasemin h)

let heapsort xs =
  let insert_value heap x = insert empty x x in  
  tolist (List.fold_left insert empty xs)


