import qualified PF as PF

-- :t map (\x -> printStrLn $ show x) [1,2,3]
-- -- język czysty potrafi opisać obliczenia z efektami ubocznymi, ale nie potrafi robić efekty uboczne

-- ghci> :t putStrLn
-- putStrLn :: String -> IO ()
-- getLine >>= putStrLn -- echo
-- ghci> getLine >>= (\x -> putStrLn $ x ++ x) -- konkatenacja
-- -----------
foo :: IO ()
foo =
  putStrLn "A"

main :: IO ()
main = do
  x <- getLine
  putStrLn x
  putStrLn x
