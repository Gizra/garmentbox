'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:ItemsAddCtrl
 * @description
 * # ItemsAddCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('ItemsAddCtrl', function ($scope, Items, Companies) {

    $scope.data = {};

    /**
     * Create a new item.
     *
     * @param data
     *   Object with data to be saved.
     */
    $scope.create = function(data) {
      // Set the company by the active one.
      data.company = Companies.getActive();
      Items.create(data).then(function() {
        $scope.data = {};
      });
    }
  });
