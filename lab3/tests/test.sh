#!/bin/bash

for i in {1..12}; do wget http://static.kremlin.ru/media/events/video/ru/video_high/S4PXYsNfjgDY48lJknqXn4bgey1Sn3W4.mp4 -e use_proxy=on -e http_proxy=127.0.0.1:8080 -O $i.mp4 & done
