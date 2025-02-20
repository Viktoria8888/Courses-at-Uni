module PF where

data Tree a
  = Leaf
  | Node (Tree a) a (Tree a)

newtype Box a = Box { unBox :: a }

data Vec = Vec { x :: Integer, y :: Integer }

type IntList = [Int]
newtype IntList = IntList { unIntList :: [Integer] }

flatTree :: Tree a -> [a]
flatTree Leaf = []
flatTree (Node l x r) = flatTree l ++ [x] ++ flatTree r

sort :: [Integer] -> [Integer] 
sort []     = []
sort (x:xs) = sort [y | y <- xs, y < x] ++ [x] ++ sort (filter (>= x) xs)

min :: [Integer] -> Integer
min = head . sort

primes :: [Integer]
primes = 2:filter isPrime [3..] where
  isPrime x = all (\p -> x `mod` p /= 0) $ takeWhile (\p -> p * p <= x) primes


