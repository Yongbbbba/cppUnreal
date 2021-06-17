#  DATETIME

```mssql
/****** Script for SelectTopNRows command from SSMS  ******/

SELECT CAST('20200425 05:03' AS DATETIME);

SELECT CURRENT_TIMESTAMP;

-- 날짜의 format이 다양함
-- YYYYMMDD
-- YYYYMMDD hh:mm:ss.nnn
-- YYYY-MM-DDThh:mm
```



서버의 경우 분산해서 여러나라에 있을 수 있는데, 그럴 때 CURRENT_TIMESTAMP를 사용하게 되면 혼란이 있을 수 있다. 그래서 GETUTCTIME() (얘는 표준sql은 아님)과 같이 시간대를 통일해서 쓰는게 정신건강에 이롭다.



많이 쓰는거

DATEADD, DATEDIFF, DATEPART

