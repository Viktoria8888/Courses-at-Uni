(* module QBF = struct
type var = string
type formula =
  | Var of var (* zmienne zdaniowe *)
  | Bot (* spójnik fałszu (⊥) *)
  | Not of formula (* negacja (¬φ) *)
  | And of formula * formula (* koniunkcja (φ ∧ ψ) *)
  | All of var * formula (* kwantyfikacja uniwersalna (∀p.φ) *)


type env = var -> bool

let rec eval (env: env) (fi: formula): bool =
  match fi with
    | Var p       -> env p
    | Bot         -> false
    | Not fi      -> not (eval env fi)
    | And(fi,psi) -> (eval env psi) && (eval env fi)
    | All(p, fi)  -> let true_env  = (fun v-> if v=p then true else env v) in
                     let false_env = (fun v-> if v=p then false else env v)in
                     (eval true_env fi) && (eval false_env fi)

let rec vars_in_formula (fi: formula) : var list =
  match fi with
    | Var p -> [p]
    | Bot -> []
    | Not fi -> vars_in_formula fi
    | And (fi, psi) -> vars_in_formula fi @ vars_in_formula psi
    | All (p, fi) -> p :: vars_in_formula fi

let rec all_assignments vars =
  match vars with
    | [] -> [fun _ -> false] 
    | y :: ys ->
      let rest = all_assignments ys in
      List.concat [
        List.map (fun env -> fun x -> if x = y then true else env x) rest;
        List.map (fun env -> fun x -> if x = y then false else env x) rest
      ]

let is_true (fi: formula) : bool =
  let vars = vars_in_formula fi in
  let assignments = all_assignments vars in
  List.for_all (fun env -> eval env fi) assignments
end
 *)
 module QBF = struct
  type var = string
  type formula =
  | Var of var               (* zmienne zdaniowe *)
  | Bot                      (* spójnik fałszu (⊥) *)
  | Not of formula           (* negacja (¬φ) *)
  | And of formula * formula (* koniunkcja (φ ∧ ψ) *)
  | All of var * formula     (* kwantyfikacja uniwersalna (∀p.φ) *)
  
  type env = var -> bool

  let extend_env : env -> var -> bool -> env =
    fun env var value ->
      fun x ->
        if x = var then value
        else env x

  let rec eval : env -> formula -> bool =
    fun env f ->
      match f with
      | Var x  -> env x
      | Bot         -> false
      | Not f -> not (eval env f)
      | And(f1, f2) -> (eval env f1) && (eval env f2)
      | All(v, f)   ->
        let env1 = extend_env env v true  in
        let env2 = extend_env env v false in
        (eval env1 f) && (eval env2 f)

  let is_true f =
    eval (fun _ -> failwith "Unbound variable") f
    
end

