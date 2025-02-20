module PF where -- jak nic nie powiemy to eksportuje wszystko



-- sort :: [Integer] -> [Integer]
-- sort xs = 
--   case xs of 
--     [] -> ...
--     x:xs -> ...
-- -- ale tak się haskelu nie pisze
-- sort []     = []
-- sort (x:xs) = filter (< x) xs ++ [x] ++ filter (>= x) xs
-- sort (x:xs) = sort [y | y <-xs, y < x] ++ [x] ++ sort (filter (>= x) xs)

-- min : [Integer] -> Integer
-- min xs = head $ sort xs -- duża złożoność. jeśli używać tylko mergesort, to O(n), bo haskel jest leniwy
-- min xs = (head . sort) xs --  kropka . złożenie funkcji
-- min = head . sort

-- isPrime :: Integer -> Bool
-- isPrime x = all (\p -> x `mod` p /=0) $ takeWhile (\p -> p * p <= x) primes
-- -- Wszystko jest wzajemnie rekurencyjne zdefiniowane na top lewelu
-- primes :: [Integer]
-- primes = 2 : filter isPrime [3..]

import Control.Monad

-- type IntList = [Int] -- to jest aliasem typu, mogą mieć parametry
-- nie można stworzyć instancji aliacji typów
-- nie można stworzyć alias 

data Tree a
  = Leaf
  | Node (Tree a) a (Tree a)
  deriving Show

newtype IntList = IntList { unIntList :: [Integer] }

data Vec2D = Vec2D
  { x :: Integer
  , y :: Integer
  }
  deriving Show

newtype Id a = Id { unId :: a } 
-- doklanie to samo co data, tylko musi byc dokladnie jeden kontruktor, 
-- ktory ma 1 parametn, poniewaz w runtime ten
-- konstruktor nie jest reprezentowany

instance Functor Id where
  fmap f m = m >>= return . f

instance Applicative Id where
  pure = return
  (<*>) = ap

instance Monad Id where
  return = Id
  Id x >>= f = f x

sort :: Ord a => [a] -> [a]
sort []     = []
sort [x]    = [x]
sort (x:xs) = sort (filter (<x) xs) ++ [x] ++ sort [y | y <- xs, y >= x ]

primes :: [Integer]
primes =
  2:filter isPrime [3..] where
    isPrime x = all (\ p -> x `mod` p /= 0) $ takeWhile (\p -> p*p <= x) primes

