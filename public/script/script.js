"use strict";

(function() {

	document.addEventListener('DOMContentLoaded', () => {
		console.log('DOMContentLoaded');

		// aos - animate
		AOS.init();

		const _colors = {
			red: 'rgb(255, 99, 132)',
			orange: 'rgb(255, 159, 64)',
			yellow: 'rgb(255, 205, 86)',
			green: 'rgb(75, 192, 192)',
			blue: 'rgb(54, 162, 235)',
			purple: 'rgb(153, 102, 255)',
			grey: 'rgb(201, 203, 207)'
		};
		
		const figureOne = document.querySelector('#figure-one').getContext('2d');
		const figureTwo = document.querySelector('#figure-two').getContext('2d');
		const figureThree = document.querySelector('#figure-three').getContext('2d');
		const figureFour = document.querySelector('#figure-four').getContext('2d');
		const figureFive = document.querySelector('#figure-five').getContext('2d');

		const _labels = [-3, -2, -1, 0, 1, 2, 3, 4];
		const _opMagnitude = {
			responsive: true,
			scales: {
				xAxes: [{
					display: true,
					scaleLabel: {
						display: true,
						labelString: 'log(ω)'
					}
				}],
				yAxes: [{
					display: true,
					scaleLabel: {
						display: true,
						labelString: '|G(jω)|dB'
					}
				}]
			}
		};
		const _opPhase = {
			responsive: true,
			scales: {
				xAxes: [{
					display: true,
					scaleLabel: {
						display: true,
						labelString: 'log(ω)'
					}
				}],
				yAxes: [{
					display: true,
					scaleLabel: {
						display: true,
						labelString: 'L G(jω)'
					}
				}]
			}
		};

		const chartOne = new Chart(figureOne, {
			type: 'line',
			data: {
				labels: _labels,
				datasets: [
					{
						label: "Asymptotic Plot",
						data: [40, 40, 40, 40, 40, 40, 40, 40],
						fill: false,
						borderColor: _colors.blue,
						lineTension: 0
					},
					{
						label: "Real Plot",
						data: [40, 40, 40, 40, 40, 40, 40, 40],
						fill: false,
						borderColor: _colors.purple,
					}
				]
			},
			options: _opMagnitude
		});
		const chartTwo = new Chart(figureTwo, {
			type: 'line',
			data: {
				labels: _labels,
				datasets: [
					{
						label: "Asymptotic Plot",
						data: [-60, -40, -20, 0, 20, 40, 60, 80],
						fill: false,
						borderColor: _colors.blue,
						lineTension: 0
					},
					{
						label: "Real Plot",
						data: [-60, -40, -20, 0, 20, 40, 60, 80],
						fill: false,
						borderColor: _colors.purple,
					}
				]
			},
			options: _opMagnitude
		});
		const chartThree = new Chart(figureThree, {
			type: 'line',
			data: {
				labels: _labels,
				datasets: [
					{
						label: "Asymptotic Plot",
						data: [60, 40, 20, 0, -20, -40, -60, -80],
						fill: false,
						borderColor: _colors.blue,
						lineTension: 0
					},
					{
						label: "Real Plot",
						data: [60, 40, 20, 0, -20, -40, -60, -80],
						fill: false,
						borderColor: _colors.purple,
					}
				]
			},
			options: _opMagnitude
		});
		const chartFour = new Chart(figureFour, {
			type: 'line',
			data: {
				labels: _labels,
				datasets: [
					{
						label: "Asymptotic Plot",
						data: [0, 0, 0, 0, 20, 40, 60, 80],
						fill: false,
						borderColor: _colors.blue,
						lineTension: 0
					},
					{
						label: "Real Plot",
						data: [0, 0, 0, 5, 20, 40, 60, 80],
						fill: false,
						borderColor: _colors.purple,
					}
				]
			},
			options: _opMagnitude
		});
		const chartFive = new Chart(figureFive, {
			type: 'line',
			data: {
				labels: _labels,
				datasets: [
					{
						label: "Asymptotic Plot",
						data: [0, 0, 0, 0, -20, -40, -60, -80],
						fill: false,
						borderColor: _colors.blue,
						lineTension: 0
					},
					{
						label: "Real Plot",
						data: [0, 0, 0, -5, -20, -40, -60, -80],
						fill: false,
						borderColor: _colors.purple,
					}
				]
			},
			options: _opMagnitude
		});
		
	});
}());