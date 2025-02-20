module NestedQBF = struct
  type empty = |

  type 'v inc = Z | S of 'v

  type 'v formula =
    | Var of 'v
    | Bot
    | Not of 'v formula
    | And of 'v formula * 'v formula
    | All of 'v inc formula

  let absurd (x : empty) = match x with | _ -> .

  type 'v env = 'v -> bool
  (* val eval : env -> formula -> bool *)

  let extend_env : type v. v env -> bool -> v inc env =
    fun env value ->
      fun x ->
        match x with
        | Z   -> value
        | S v -> env v

  let rec eval : type v. v env -> v formula -> bool =
    fun env f ->
    match f with
    | Var x       -> env x
    | Bot         -> false
    | Not f       -> not (eval env f)
    | And(f1, f2) -> (eval env f1) && (eval env f2)
    | All f   ->
      let env1 = extend_env env true  in
      let env2 = extend_env env false in  
      (eval env1 f) && (eval env2 f)

  let is_true : empty formula -> bool =
    fun f ->
      eval absurd f
      
end