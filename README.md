# **鬼島馬路**開發紀錄
# 總結
* 美術圖要快點生出來

## 2021/12/18
* github remote端加入.gitignore，用來忽略編譯的檔案
* github remote端加入README.md，紀錄開發進度
* 目前正在LOCAL端開發的工具
	* Imagx(載2D圖片用)
		* 目前支援jpg,png
		* 讀失真壓縮的檔案會出事
	* ObjLoader(匯入3D模型，目前沒有貼圖功能)

## 2021/12/07
* 是否需要處理加速度
	* 加速時，"外送員"看起來會比較前面[相對位移]
* CollisionBall為碰撞球，有中心點及半徑，需要用函數檢查兩顆球是否有碰撞
* Event為意外事件，若偵測與"外送員"相撞則遊戲結束，並播放獲得鬼島馬路成就
	* 有各種事件，可能還要另外寫物件
	* 招牌看板
	* 逆向車
	* 圓孔蓋
	* 飛來橫禍
	* 地府火焰(氣爆)
	* 老奶奶過馬路(機車一些，不走斑馬線)

