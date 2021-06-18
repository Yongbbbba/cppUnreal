# GROUP BY

```mssql
-- playerID (선수ID)
-- yearID (시즌 년도)
-- teamID (팀 명칭, 'BOS' = 보스턴)
-- G_batting(출전 경기 + 타석)

-- AB(타수)
-- H(안타)
-- R(출루)
-- 2B(2루타)
-- HR(홈런)
-- 3B(3루타)
-- BB(볼넷)


-- 2004년도에 가장 많은 홈런을 날린 팀은?
SELECT TOP 1 teamID, SUM(HR) AS HOMERUNS
FROM batting
WHERE yearID = 2004
GROUP BY teamID
ORDER BY SUM(HR) DESC;

-- 2004년도에 200홈런 이상을 날린 팀의 목록?
SELECT teamID, SUM(HR)
FROM batting
WHERE yearID = 2004
GROUP BY teamID
HAVING SUM(HR) >= 200
ORDER BY SUM(HR) DESC;

-- FROM 책상에서
-- WHERE 공을
-- GROUP BY 색상별로 분류해서
-- HAVING 분류한 다음에 빨간색은 제외하고 
-- SELECT 갖고 와서 
-- ORDER BY 크기 별로 나열해주세요
-- 이 순서대로 실제 쿼리가 실행된다.

-- 단일 년도에 가장 많은 홈런을 날린 팀은?
SELECT teamID, yearID, SUM(HR) AS homeruns
FROM batting
GROUP BY teamID, yearID
ORDER BY homeruns DESC;
```

