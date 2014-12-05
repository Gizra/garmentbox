'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:MainCtrl
 * @description
 * # MainCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('MainCtrl', function ($scope, Items, ItemVariants, $log) {

    $scope.items = null;
    $scope.selectedItem = null;
    $scope.itemVariants = null;
    $scope.selectedItemVariants = null;

    $scope.$on('$stateChangeSuccess', function(event, toState, toParams, fromState){
      if (toState.name.startsWith('dashboard')) {
        // Load items.
        Items.get().then(function(items) {
          $scope.items = items;

          setSelectedItem(toState, toParams);
          setSelectedItemVariant(toState, toParams);
        });
      }
    });

    /**
     * Set the selected item.
     *
     * @param toState
     * @param toParams
     */
    var setSelectedItem = function(toState, toParams) {
      if (!toState.name.startsWith('dashboard.item')) {
        return;
      }
      var id = toParams.id;

      angular.forEach($scope.items, function(value, key) {
        if (value.id == id) {
          $scope.selectedItem = value;
        }
      });

      ItemVariants.get(id).then(function(itemVariants) {
        $scope.itemVariants = itemVariants;
      });
    };

    /**
     * Set the selected item variant.
     *
     * @param toState
     * @param toParams
     */
    var setSelectedItemVariant = function(toState, toParams) {
      if (!toState.name.startsWith('dashboard.item.variant')) {
        return;
      }

      var id = toParams.variant;

      ItemVariants.get(id).then(function(itemVariants) {
        angular.forEach($scope.itemVariants, function(value, key) {
          if (value.id == id) {
            $scope.selectedItemVariant = value;
          }
        });
      });
    }
  });
