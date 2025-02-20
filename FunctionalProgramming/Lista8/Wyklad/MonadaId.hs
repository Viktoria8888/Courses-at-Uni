echo :: IO ()
echo = do
  putStrLn "ECHO:"
  x <- getLine
  putStrLn x

{- comment -}
-- echo = putStrLn "ECHO:" >> getLine >>= \ x -> putStrLn x

main :: IO ()
main = do
  putStrLn "Hello World!!!"
  echo
