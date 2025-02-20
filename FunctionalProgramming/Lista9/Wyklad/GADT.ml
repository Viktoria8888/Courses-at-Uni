type _ tp =
  | Unit   : unit tp
  | Int    : int  tp
  | Bool   : bool tp
  | String : string tp
  | Pair   : 'a tp * 'b tp -> ('a * 'b) tp
  | List   : 'b tp -> 'b list tp

let rec print : type a. a tp -> a -> string =
  fun tp x ->
  match tp with
  | Unit   -> "()"
  | Int    -> string_of_int x
  | Bool   -> string_of_bool x
  | String -> "\"" ^ String.escaped x ^ "\""
  | Pair(tp1, tp2) -> "(" ^ print tp1 (fst x) ^ "," ^ print tp2 (snd x) ^ ")"
  | List tp -> "[" ^ String.concat ";" (List.map (print tp) x) ^ "]"

