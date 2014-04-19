import Control.Applicative ((<$>))
import Control.Monad

main = do
  t <- readLn
  inputs <- map (map read . tail . words) <$> replicateM t getLine :: IO [[Integer]]
  forM_ (zip [1..t] inputs) $ \(i,ns) ->
    let g = foldl1 gcd (diffs ns)
        a = (g - head ns `mod` g) `mod` g
    in putStrLn $ "Case #" ++ show i ++ ": " ++ show a

diffs :: [Integer] -> [Integer]
diffs [] = []
diffs (n:ns) = map (abs . subtract n) ns ++ diffs ns

