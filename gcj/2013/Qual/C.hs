import Control.Applicative ((<$>))
import Control.Monad (forM_)
import Text.Printf (printf)

main :: IO ()
main = do
  t <- readLn
  forM_ [1::Int .. t] $ \ti -> do
    [a, b] <- map read . words <$> getLine
    printf "Case #%d: %d\n" ti $ length $ filter isPalindrome $ takeWhile (<= b) $ dropWhile (< a) xs

xs :: [Integer]
xs = map (\n -> n*n) $ filter isPalindrome [1..]

isPalindrome :: Integer -> Bool
isPalindrome n = let s = show n in s == reverse s
