'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:MainCtrl
 * @description
 * # MainCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('MainCtrl', function ($scope, Items) {

    $scope.$on('$stateChangeSuccess', function(event, toState){
      //Meter Principal dashboard view.
      if (toState.name === 'dashboard') {
        // Load meters.
        Items.get().then(function(items) {
          $scope.items = items;
        });
      }
    });
  });
