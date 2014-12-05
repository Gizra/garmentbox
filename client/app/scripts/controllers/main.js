'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:MainCtrl
 * @description
 * # MainCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('MainCtrl', function ($scope, Items, $log) {

    $scope.$on('$stateChangeSuccess', function(event, toState, toParams, fromState){
      if (toState.name.startsWith('dashboard')) {
        // Load items.
        $scope.selectedItem = null;

        Items.get().then(function(items) {
          $scope.items = items;

          setSelectedItem(toState, toParams);
          setSelectedItemVariant(toState, toParams);
        });
      }
    });

    var setSelectedItem = function(toState, toParams) {
      if (!toState.name.startsWith('dashboard.item')) {
        return;
      }
      var id = toParams.id;

      angular.forEach($scope.items, function(value, key) {
        if (value.id == id) {
          $scope.selectedItem = value;
          $log.log($scope.selectedItem);
        }
      });
    };

    var setSelectedItemVariant = function(toState, toParams) {
      if (!toState.name.startsWith('dashboard.item.variant')) {
        return;
      }
    }
  });
