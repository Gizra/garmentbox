'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:MainCtrl
 * @description
 * # MainCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('ItemsCtrl', function ($scope, items, itemVariants, $state, $log) {

    // Initialize values.
    $scope.items = items;
    $scope.selectedItem = null;

    $scope.itemVariants = itemVariants;
    $scope.selectedItemVariants = null;

    $scope.$on('$stateChangeSuccess', function(event, toState, toParams){
      if (!$state.includes('dashboard.items')) {
        return;
      }


      if (toParams.id) {
        setSelectedItem(toParams.id);
      }

      if (toParams.variant) {
        setSelectedItemVariant(toParams.variant);
      }
    });

    /**
     * Set the selected item.
     *
     * @param int id
     *   The item ID.
     */
    var setSelectedItem = function(id) {
      $scope.selectedItem = null;

      angular.forEach($scope.items, function(value) {
        if (value.id == id) {
          $scope.selectedItem = value;
        }
      });
    };

    /**
     * Set the selected item variant.
     *
     * @param int id
     *   The item variant ID.
     */
    var setSelectedItemVariant = function(id) {
      $scope.selectedItemVariant = null;

      angular.forEach($scope.itemVariants, function(value) {
        if (value.id == id) {
          $scope.selectedItemVariant = value;
        }
      });
    }
  });
