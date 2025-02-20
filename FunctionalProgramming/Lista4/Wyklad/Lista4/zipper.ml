type 'a tree =
  | Leaf
  | Node of 'a tree * 'a * 'a tree

type 'a context =
  | Root
  | Left of 'a context * 'a * 'a tree
  | Right of 'a tree * 'a * 'a context

type 'a zipper = 'a context * 'a tree

let rec plug ctx t =
  match ctx with
  | Root -> t
  | Left(ctx, x, r) -> plug ctx (Node(t, x, r))
  | Right(l, x, ctx) -> plug ctx (Node(l, x, t))

let of_tree t = (Root, t)

let to_tree (ctx, t) = plug ctx t

let go_up (ctx, t) =
  match ctx with
  | Root -> failwith "up"
  | Left(ctx, x, r) -> (ctx, Node(t, x, r))
  | Right(l, x, ctx) -> (ctx, Node(l, x, t))

let go_left (ctx, t) =
  match t with
  | Leaf -> failwith "left"
  | Node(l, x, r) -> (Left(ctx, x, r), l)

let go_right (ctx, t) =
  match t with
  | Leaf -> failwith "right"
  | Node(l, x, r) -> (Right(l, x, ctx), r)

let get_label (_, t) =
  match t with
  | Leaf -> failwith "get_label"
  | Node(_, x, _) ->x

let set_label (ctx, t) x =
  match t with
  | Leaf -> failwith "set_label"
  | Node(l, _, r) -> (ctx, Node(l, x, r))

let get_subtree (_, t) = t

let set_subtree (ctx, _) t = (ctx, t)
