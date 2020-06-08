"use strict";

(function() {
	
	/***********************************************************************************************
	 * Global functions
	 */
	
	function _hide(e) {
		e.classList.remove('reveale-view');
		e.classList.add('hide-view');
	}

	function _reveal(e) {
		e.classList.remove('hide-view');
		e.classList.add('reveale-view');
	}

	function printErrors(errors) {
		errorList.innerHTML = '';

		errors.forEach((error, i) => {
			const e = document.createElement('div');
			e.className = 'alert alert-danger hide-view';
			e.innerText = error;
			errorList.appendChild(e);
			
			setTimeout(() => {
				_reveal(e);
			}, 100 + 30 * i);
		});
	}
	window.printErrors = printErrors;

	function calculatePlot(text) {
		const { CalculatePlot } = Module;
		CalculatePlot(text);
		// revealCalculated();
	}

	/***********************************************************************************************
	 * Listeners 
	 */ 

	let Plots,
			Options,
			ModuleDatasets,
			PhaseDatasets;

	function generateModulePhaseButtonsListeners() {
		const moduleButtons = Array.from(document.querySelectorAll('.module-button'));
		const phaseButtons = Array.from(document.querySelectorAll('.phase-button'));

		const activeStyle = 'border-teal-400 border-b-2 px-3';
		const notActiveStyle = 'text-white bg-teal-400 px-3';

		for (let i = 0; i < 5; i += 1) {

			const moduleB = moduleButtons[i];
			const phaseB = phaseButtons[i];

			const moduleData = ModuleDatasets[i];
			const phaseData = PhaseDatasets[i];

			const chart = Plots[i];

			moduleB.addEventListener('click', () => {
				phaseB.className = notActiveStyle;
				moduleB.className = activeStyle;

				chart.data.datasets = moduleData;
				chart.options = Options._opModule;
				chart.update();
			});

			phaseB.addEventListener('click', () => {
				phaseB.className = activeStyle;
				moduleB.className = notActiveStyle;
				
				chart.data.datasets = phaseData;
				chart.options = Options._opPhase;
				chart.update();
			});

		}

	}

	function generateFormListeners() {

		const generateButton = document.querySelector('#generate-button');
		const newButton = document.querySelector('#new-button');
		
		const formView = document.querySelector('.form-formula');
		formView.classList.add('reveale-view');

		const newView = document.querySelector('.new-button');
		newView.classList.add('hide-view');

		const calculated = document.querySelector('.calculated-graph');
		calculated.classList.add('hide-view');

		function revealCalculated() {
			_reveal(calculated);
			_reveal(newView);
			_hide(formView);
		}
		window.revealCalculated = revealCalculated;

		generateButton.addEventListener('click', () => {

			const text = document.getElementById("function-input").value;
			errorList.innerHTML = '';
			
			if (text.length) 
				calculatePlot(text);
			else 
				printErrors([
					"The function can not be empty.",
				]);
		});

		newButton.addEventListener('click', () => {
			_hide(calculated);
			_hide(newView);
			_reveal(formView);
		});

	}

	function GenerateCalculatedPlotListeners(moduleData, phaseData) {
		
		console.log(moduleData, phaseData);
		
		const wrapper = document.querySelector('.button-wrapper');
		wrapper.innerHTML = '';

		(function() {
			const moduleB = document.createElement('button')
			moduleB.className = 'calculated-module-button ';
			moduleB.innerText = 'Module';

			const phaseB = document.createElement('button')
			phaseB.className = 'calculated-phase-button ';
			phaseB.innerText = 'Phase';

			wrapper.appendChild(moduleB);
			wrapper.appendChild(phaseB);
		}());

		const moduleB = document.querySelector('.calculated-module-button');
		const phaseB = document.querySelector('.calculated-phase-button');

		const activeStyle = 'border-teal-400 border-b-2 px-3';
		const notActiveStyle = 'text-white bg-teal-400 px-3';

		moduleB.className += activeStyle;
		phaseB.className += notActiveStyle;

		const _labels = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];

		const chart = new Chart(document.querySelector('#plot-c').getContext('2d'), {
			type: 'line',
			data: {
				labels: _labels,
				datasets: [
					{
						label: "Real Plot",
						data: moduleData,
						fill: false,
						borderColor: 'rgb(54, 162, 235)',
						lineTension: 1
					}
				]
			},
			options: Options._opModule
		});

		moduleB.addEventListener('click', () => {
			phaseB.className = notActiveStyle;
			moduleB.className = activeStyle;

			chart.data.datasets = [
				{
					label: "Real Plot",
					data: moduleData,
					fill: false,
					borderColor: 'rgb(54, 162, 235)',
					lineTension: 0.2
				}
			];
			chart.options = Options._opModule;
			chart.update();
		});

		phaseB.addEventListener('click', () => {
			phaseB.className = activeStyle;
			moduleB.className = notActiveStyle;
			
			chart.data.datasets = [
				{
					label: "Real Plot",
					data: phaseData,
					fill: false,
					borderColor: 'rgb(54, 162, 235)',
					lineTension: 0.2
				}
			];
			chart.options = Options._opPhase;
			chart.update();
		});
		
		// download
		const downloadButton = document.querySelector('#download-button');
		downloadButton.addEventListener('click', () => {

		});
	}
	window.GenerateCalculatedPlotListeners = GenerateCalculatedPlotListeners;

	function generateListeners() {
		generateModulePhaseButtonsListeners();
		generateFormListeners();
	}


	/***********************************************************************************************
	 * Entry point
	 */
	document.addEventListener('DOMContentLoaded', () => {
		console.log('DOMContentLoaded');
		const errorList = document.querySelector('#error-list');
		window.errorList = errorList;
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

		const moduleOne = [
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
		];
		const moduleTwo = [
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
		];
		const moduleThree = [
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
		];
		const moduleFour = [
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
		];
		const moduleFive = [
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
		];

		const phaseOne = [
			{
				label: "Asymptotic Plot",
				data: [3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14],
				fill: false,
				borderColor: _colors.blue,
				lineTension: 0
			},
			{
				label: "Real Plot",
				data: [3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14],
				fill: false,
				borderColor: _colors.purple,
			}
		];
		const phaseTwo = [
			{
				label: "Asymptotic Plot",
				data: [1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57],
				fill: false,
				borderColor: _colors.blue,
				lineTension: 0
			},
			{
				label: "Real Plot",
				data: [1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57],
				fill: false,
				borderColor: _colors.purple,
			}
		];
		const phaseThree = [
			{
				label: "Asymptotic Plot",
				data: [-1.57, -1.57, -1.57, -1.57, -1.57, -1.57, -1.57, -1.57],
				fill: false,
				borderColor: _colors.blue,
				lineTension: 0
			},
			{
				label: "Real Plot",
				data: [-1.57, -1.57, -1.57, -1.57, -1.57, -1.57, -1.57, -1.57],
				fill: false,
				borderColor: _colors.purple,
			}
		];
		const phaseFour = [
			{
				label: "Asymptotic Plot",
				data: [0, 0, 0, 0.78, 1.57, 1.57, 1.57, 1.57],
				fill: false,
				borderColor: _colors.blue,
				lineTension: 0
			},
			{
				label: "Real Plot",
				data: [0, 0, 0.10, 0.78, 1.47, 1.57, 1.57, 1.57],
				fill: false,
				borderColor: _colors.purple,
			}
		];
		const phaseFive = [
			{
				label: "Asymptotic Plot",
				data: [0, 0, 0, -0.78, -1.57, -1.57, -1.57, -1.57],
				fill: false,
				borderColor: _colors.blue,
				lineTension: 0
			},
			{
				label: "Real Plot",
				data: [0, 0, -0.10, -0.78, -1.47, -1.57, -1.57, -1.57],
				fill: false,
				borderColor: _colors.purple,
			}
		];

		const _opModule = {
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
				datasets: moduleOne
			},
			options: _opModule
		});
		const chartTwo = new Chart(figureTwo, {
			type: 'line',
			data: {
				labels: _labels,
				datasets: moduleTwo
			},
			options: _opModule
		});
		const chartThree = new Chart(figureThree, {
			type: 'line',
			data: {
				labels: _labels,
				datasets: moduleThree
			},
			options: _opModule
		});
		const chartFour = new Chart(figureFour, {
			type: 'line',
			data: {
				labels: _labels,
				datasets: moduleFour
			},
			options: _opModule
		});
		const chartFive = new Chart(figureFive, {
			type: 'line',
			data: {
				labels: _labels,
				datasets: moduleFive
			},
			options: _opModule
		});
		
		Plots = [ chartOne, chartTwo, chartThree, chartFour, chartFive ];
		Options = { _opModule, _opPhase };
		ModuleDatasets = [ moduleOne, moduleTwo, moduleThree, moduleFour, moduleFive ];
		PhaseDatasets = [ phaseOne, phaseTwo, phaseThree, phaseFour, phaseFive ];

		// activating all listeners
		generateListeners();

	});
}());